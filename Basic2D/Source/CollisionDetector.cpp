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

    bool collision = (overlaps.size() == normals.size());

    if(collision) 
        return axis_least_penetration.normalize() * penetration_depth;
    else
        return Vector(0, 0);
}

Vector CollisionDetector::get_contact_point(Object *a, Object *b, Vector axis_least_penetration) {

    Object *incident  = a;
    Object *reference = b;

    Vector collision_axis_normalized = axis_least_penetration.normalize();

    // Find reference and incident object
    bool a_is_reference = CollisionDetector::get_reference_object(a, b, collision_axis_normalized);

    if(a_is_reference) {
        reference = a;
        incident = b;
    }
    
    vector<Vector> contact_points = CollisionDetector::clip(reference, incident, 0,
                                                            axis_least_penetration);

    // Take contact point as support point of incident object
    return CollisionDetector::get_support_point(incident, collision_axis_normalized * -1);
}

/**
    Determines the reference objects

    Param: objects and axis of penetration
    Return: Index of reference face so that the reference is between
    index and index+1.Returns negative index if b is the reference

    TODO: Needs to return start reference face index or else
    I would have to calculate it again later which might get slow
*/
bool CollisionDetector::get_reference_object(Object *a, Object *b, Vector axis_normalized) {

    vector<Vector> normals_a = a->get_normals();
    vector<Vector> normals_b = b->get_normals();
    double best_a = normals_a.at(0).dot(axis_normalized);

    if(normals_a.size() > 1) {
        
        for(unsigned int i = 1; i < normals_a.size(); i++) {
            
            double normal_value = normals_a.at(i).dot(axis_normalized);
            if(normal_value > best_a)
                best_a = normal_value;
        }
    }

    double best_b = normals_b.at(0).dot(axis_normalized);

    if(normals_b.size() > 1) {

        for(unsigned int i = 1; i < normals_b.size(); i++) {

            double normal_value = normals_b.at(i).dot(axis_normalized);

            if(normal_value > best_b)
                best_b = normal_value;
        }
    }

    if(best_a > best_b)
        return true;
    else
        return false;
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

/**
    Clips colliding polygons to find contact points

    Param: Objects involved in collision and axis assiciated
    Return: Contact points
*/
vector<Vector> CollisionDetector::clip(Object* reference, Object* incident,
                                       unsigned int vertex_index, Vector axis) {

    /*
        unsigned int index = 0;
        Vector v1     = objects.at(0)->get_vertices().at(index);
        Vector v2     = objects.at(0)->get_vertices().at(index+1);
        Vector pos    = *objects.at(0)->get_position();
        Vector edge   = (v2-pos) - (v1-pos);
        Vector normal = objects.at(0)->get_normals().at(index);
    
        Vector v_start = reference->get_vertices.at(vertex_index);
        Vector v_end   = reference->get_vertices.at(vertex_index + 1);
        Vector pos     = *reference->get_position();
        Vector clipping_face        = (v_end - pos) - (v_start - pos);
        Vector clipping_face_normal = reference->get_normals().at(vertex_index);
    */ 

    vector<Vector> output;
    output.push_back(Vector(0, 0));
    return output;
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

void CollisionDetector::compute_apply_positional_correction(Object *object, Collision *collision) {

    Vector correction = *collision->get_axis();
    Vector corrected_position = *object->get_position() + correction;

    object->set_position(corrected_position);
}

vector<Vector> CollisionDetector::merge_Vector(vector<Vector> vectors_a, vector<Vector> vectors_b) {

    vector<Vector> output;
    output = vectors_a;

    for(unsigned int i = 0; i < vectors_b.size(); i++) {

        output.push_back(vectors_b.at(i));
    }

    return output;
}

