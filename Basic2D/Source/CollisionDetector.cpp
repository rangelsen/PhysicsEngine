#include <vector>
#include <iostream>
#include <cmath>

#include "CollisionDetector.h"
#include "Object.h"
#include "Vector.h"
#include "Display.h"
#include "Collision.h"
#include "World.h"

#define INF 100000
using namespace std;

Vector CollisionDetector::collision_detection_SAT(Object *a, Object *b) {

    vector<Vector> vertices_a = a->get_vertices();
    vector<Vector> vertices_b = b->get_vertices();
    vector<Vector> normals_a  = a->get_normals();
    vector<Vector> normals_b  = b->get_normals();

    vector<Vector> normals = CollisionDetector::merge_Vector(normals_a, normals_b);

    Vector current_normal = normals_a.at(0);

    double min_a, max_a;
    double min_b, max_b;

    vector<bool> overlaps;

    Vector axis_least_penetration(2);

    double penetration_depth = -INF;

    for(unsigned int i = 0; i < normals.size(); i++) {

        current_normal = normals.at(i);

        min_a = vertices_a.at(0).dot(current_normal);
        max_a = min_a;

        min_b = vertices_b.at(0).dot(current_normal);
        max_b = min_b;

        for(unsigned int j = 1; j < vertices_a.size(); j++) {

            double scalar_projection = vertices_a.at(j).dot(current_normal);

            if(scalar_projection < min_a) {
                min_a = scalar_projection;
            }
            
            if(scalar_projection > max_a) {
                max_a = scalar_projection;
            }
        }

        for(unsigned int j = 1; j < vertices_b.size(); j++) {

            double scalar_projection = vertices_b.at(j).dot(current_normal);

            if(scalar_projection < min_b) {
                min_b = scalar_projection;
            }
            if(scalar_projection > max_b) {
                max_b = scalar_projection;
            }
        }


        double test_1 = min_b - max_a;
        double test_2 = min_a - max_b;

        if(!(test_1 > 0) && !(test_2 > 0)) {

            if(test_1 > penetration_depth) {

                axis_least_penetration = current_normal;
                penetration_depth = test_1;
            }
            
            if(test_2 > penetration_depth) {

                axis_least_penetration = current_normal;
                penetration_depth = test_2;
            }

            overlaps.push_back(false);
        }
    }

    Vector c = get_contact_point(a, b, axis_least_penetration);

    bool collision = (overlaps.size() == normals.size()) ? true : false;

    if(collision) 
        return axis_least_penetration.normalize() * penetration_depth;
    else
        return Vector(0, 0);
}

// ************ WARNING line 5 ************* switched a and b
Vector CollisionDetector::get_contact_point(Object *a, Object *b, Vector axis_least_penetration) {

    bool debug = false;

    // Determine which object contains reference face
    bool b_is_reference = CollisionDetector::get_reference_object(b, a, axis_least_penetration);

    Object *incident  = a;
    Object *reference = b;

    if(!b_is_reference) {
    
        incident  = b;
        reference = a;
    }

    if(debug) {
        Display::object(*reference, BLUE);
        Display::object(*incident, BLUE);
    }

    return CollisionDetector::get_support_point(incident, axis_least_penetration * -1);
}

bool CollisionDetector::get_reference_object(Object *a, Object *b, Vector axis_least_penetration) {

    double distance_along_axis_a = a->get_position()->dot(axis_least_penetration);
    double distance_along_axis_b = b->get_position()->dot(axis_least_penetration);

    if(distance_along_axis_a < distance_along_axis_b)
        return true;
    else
        return false;
}

vector<Vector> CollisionDetector::merge_Vector(vector<Vector> vectors_a, vector<Vector> vectors_b) {

    vector<Vector> output;
    output = vectors_a;

    for(unsigned int i = 0; i < vectors_b.size(); i++) {

        output.push_back(vectors_b.at(i));
    }

    return output;
}

Vector CollisionDetector::get_support_point(Object *object, Vector axis) {

    Vector support_point = object->get_vertices().at(0);
    double distance_along_axis = support_point.dot(axis);

    for(unsigned int i = 1; i < object->get_vertices().size(); i++) {

        Vector current_vertex = object->get_vertices().at(i);
        double distance = current_vertex.dot(axis);

        if(distance > distance_along_axis) {
            
            support_point = current_vertex;
            distance_along_axis = distance;
        }
    }

    return support_point;
}

unsigned int CollisionDetector::get_support_point_index(Object *object, Vector axis) {

    unsigned int index = 0;
    Vector support_point = object->get_vertices().at(0);
    double distance_along_axis = support_point.dot(axis);

    for(unsigned int i = 1; i < object->get_vertices().size(); i++) {

        Vector current_vertex = object->get_vertices().at(i);
        double distance = current_vertex.dot(axis);

        if(distance > distance_along_axis) {
            
            support_point = current_vertex;
            distance_along_axis = distance;
            index = i;
        }
    }

    return index;
}


Vector CollisionDetector::get_most_orthogonal_face(Object *object, Vector axis) {

    unsigned int support_point_index = CollisionDetector::get_support_point_index(object, axis);
    unsigned int next_point_index, prev_point_index;

    if(support_point_index == 0) {

        next_point_index = support_point_index + 1;
        prev_point_index = object->get_vertices().size() - 1;
    }
    else if(support_point_index == object->get_vertices().size() - 1) {

        next_point_index = 0;
        prev_point_index = support_point_index - 1;
    }
    else {

        next_point_index = support_point_index + 1;
        prev_point_index = support_point_index - 1;
    }

    Vector prev_face = object->get_vertices().at(support_point_index) - object->get_vertices().at(prev_point_index);
    Vector next_face = object->get_vertices().at(next_point_index) - object->get_vertices().at(support_point_index);

    if(abs(prev_face.dot(axis)) > abs(next_face.dot(axis)))
        return next_face;
    else
        return prev_face;
}

vector<Collision*> CollisionDetector::get_collisions(World *world) {
    
    vector<Collision*> collisions;

    vector<Object*> objects = world->get_objects();

    for(unsigned int i = 0; i < objects.size(); i++) {
        Object *object_a = objects.at(i);

        if(i < objects.size() - 1) {
            for(unsigned int j = i + 1; j < objects.size(); j++) {
                Object *object_b = objects.at(j);

                Vector axis_least_penetration = CollisionDetector::collision_detection_SAT(object_a, object_b);

                if(!(axis_least_penetration == Vector(0, 0))) {

                    Vector contact_point = CollisionDetector::get_contact_point(object_a, object_b, axis_least_penetration);

                    Collision *collision = new Collision(object_a, object_b, axis_least_penetration, contact_point);

                    collisions.push_back(collision);
                }
            }
        }
    }

    return collisions;
}