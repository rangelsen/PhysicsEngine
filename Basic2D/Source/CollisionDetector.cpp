#include <vector>
#include <iostream>
#include <cmath>
#include <utility>

#include "CollisionDetector.h"
#include "Object.h"
#include "Vector.h"
#include "Display.h"
#include "Collision.h"
#include "World.h"

#define INF 100000
using namespace std;

/**
    Determines of objects a and b collide

    Param: Objects to test for collision
    Return: Pair consisting of a flag for
    collision and the axis of least separation
    which is the vector pointing from b to a
*/
pair<bool, Vector> CollisionDetector::collision_detection_SAT(Object *a, Object *b) {

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

            if(scalar_projection < min_b)
                min_b = scalar_projection;
            if(scalar_projection > max_b)
                max_b = scalar_projection;
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

    bool collision = (overlaps.size() == normals.size());
    Vector axis_normalized = axis_least_penetration.normalize() * penetration_depth;

    return make_pair(collision, axis_normalized);
}

/**
    Finds the contact point of the collision
    between object a and object b

    Param: Objects involved in collision,
    and collision axis of penetration
    Return: Contact point

    TODO: Verify that the clipping works
    TODO: Implement Object::get_edge()
    TODO: Implement CollDet::get_best_vertex
*/
vector<Vector> CollisionDetector::get_contact_points(Object *a, Object *b, Vector axis) {

    cout << "DEBUG: #1" << endl;
    Vector axis_n = axis.normalize();

    /* Make sure a and b are correct */
    bool flip = CollisionDetector::flip_objects(a, b, axis_n);
    if(flip) {
        Object* temp = a;
        a = b;
        b = temp;
    }

    /* Find best edges of a and b */
    // TODO: get_best_edge_index not correctly implemented
    int a_best_index = a->get_best_edge_index(axis_n);
    int b_best_index = b->get_best_edge_index(axis_n * -1);
    Vector a_best = a->get_edge(a_best_index);
    Vector b_best = b->get_edge(b_best_index);

    /* Find the reference edge */
    Vector ref(0, 0);
    Vector inc(0, 0);
    bool b_is_ref = true;

    if(abs(axis_n.dot(a_best)) >= abs(axis_n.dot(b_best))) {
        ref = b_best;
        inc = a_best;
    }
    else {
        ref = a_best;
        inc = b_best;
        b_is_ref = false;
    }

    vector<Vector> vertices_a = a->get_vertices();
    vector<Vector> vertices_b = b->get_vertices();

    cout << "DEBUG: #2" << endl;
    /* First clipping operation */
    Vector ref_n = ref.normalize();
    Vector v1_inc(0, 0);
    Vector v2_inc(0, 0);
    Vector v1_ref(0 ,0);
    Vector v2_ref(0, 0);
    Vector ref_normal(0, 0);

    double offset;

    // TODO: Error in this block with indices
    if(b_is_ref) {
        v1_inc = vertices_a.at(a_best_index);
        v2_inc = vertices_a.at(a_best_index + 1);
        v1_ref = vertices_b.at(b_best_index);
        v2_ref = vertices_b.at(b_best_index + 1);
        ref_normal = b->get_normals().at(b_best_index).normalize() * -1;
    }
    else {
        v1_inc = vertices_b.at(b_best_index);
        v2_inc = vertices_b.at(b_best_index + 1);
        v1_ref = vertices_a.at(a_best_index);
        v2_ref = vertices_a.at(a_best_index + 1);
        ref_normal = a->get_normals().at(a_best_index).normalize() * -1;
    }

    offset = -ref_n.dot(v1_ref);
    vector<Vector> clipped_points = CollisionDetector::clip(v1_inc, v2_inc, ref_n, offset);

    if(clipped_points.size() < 2)
        Display::error("Clipping #1 failed");

    /* Second clipping operation */
    cout << "DEBUG: #3" << endl;

    offset = ref_n.dot(v2_ref);
    clipped_points = CollisionDetector::clip(clipped_points.at(0), clipped_points.at(1), ref_n * -1, offset);
    
    if(clipped_points.size() < 2)
        Display::error("Clipping #2 failed");

    /* Third clipping operation */
    cout << "DEBUG: #4" << endl;

    double depth_1 = ref_normal.dot(clipped_points.at(0) - v1_ref);
    double depth_2 = ref_normal.dot(clipped_points.at(1) - v1_ref);

    if(depth_1 >= 0.0) clipped_points.erase(clipped_points.begin());
    if(depth_2 >= 0.0) clipped_points.erase(clipped_points.end());
    
    return clipped_points;

    /* Take contact point as support point of incident object */
    // return CollisionDetector::get_support_point(incident, collision_axis_normalized * -1);
}

/**
    Determines the reference objects

    Param: Objects and axis of penetration
    Return: true if the axis points from a to b.
    return false otherwise
*/
bool CollisionDetector::flip_objects(Object *a, Object *b, Vector axis_normalized) {

    Vector ab = *b->get_position() - *a->get_position();
    
    if(ab.dot(axis_normalized) < 0)
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
    Clips the incident edge's vertices along the
    reference edge, given the offset

    @param: Incident vertices, normalized reference vector,
            offset from where to start clipping
    @return: Contact points

    TODO: If it's not tested it's broken!
*/

vector<Vector> CollisionDetector::clip(Vector v1, Vector v2, Vector n, double offset) {
    vector<Vector> clipped_points;    
    
    double d1 = n.dot(v1) - offset;
    double d2 = n.dot(v2) - offset;

    if(d1 >= 0.0) clipped_points.push_back(v1);
    if(d2 >= 0.0) clipped_points.push_back(v2);

    if(d1 * d2 < 0.0) {
        Vector diff = v2 - v1;
        double slope = d1 /(d2 - d1);
        diff *= slope;
        Vector new_point = diff + v1;
        clipped_points.push_back(new_point);
    }

    return clipped_points;
}

/*
vector<Vector> CollisionDetector::clip(Object* reference, Object* incident,
                                       int start_vertex_index, Vector axis) {

    vector<Vector> normals_ref    = reference->get_normals();
    vector<Vector> vertices_inc   = incident->get_vertices();
    vector<Vector> contact_points = incident->get_vertices();

    for(size_t i = 0; i < 3; i++) {
        
        int normal_index       = (start_vertex_index - 1 + i) % normals_ref.size();
        Vector clipping_normal = normals_ref.at(normal_index) * -1;

        if(normal_index >= normals_ref.size())
            normal_index = (normals_ref.size() - 1 + normal_index) % normals_ref.size();

        for(int j = contact_points.size() - 1; j >= 0; j--) {
            Vector local_vertex = vertices_inc.at(j) - *incident->get_position();

            if(clipping_normal.dot(local_vertex) < 0) {
               contact_points.at(j) = contact_points.back();
               contact_points.pop_back();
            }
        }
    }

    return contact_points;

}
*/
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

                Object *object_b                    = objects.at(j);
                pair<bool, Vector> collision_status = CollisionDetector::collision_detection_SAT(object_a, object_b);
                bool has_collision                  = get<0>(collision_status);
                Vector axis_least_penetration       = get<1>(collision_status);

                if(has_collision) {
                    Display::message("has collision", RED);
                    Display::vector(axis_least_penetration, WHITE);
                    vector<Vector> contact_points = CollisionDetector::get_contact_points(object_a, object_b, axis_least_penetration);
                    for(size_t k = 0; k < contact_points.size(); k++)
                        collisions.push_back(new Collision(object_a, object_b, axis_least_penetration, contact_points.at(k)));
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

