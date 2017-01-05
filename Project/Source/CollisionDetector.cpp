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
#include "Scene.h"

#define INF 100000

using namespace std;

/**
    Determines of objects a and b collide

    @param: Objects to test for collision
    @return: Pair consisting of a flag for
             collision and the axis of least separation
             which is the vector pointing from a to b
*/
pair<bool, Vector> CollisionDetector::collision_detection_SAT(Object *a, Object *b) {

    vector<Vector> vertices_a = a->get_vertices();
    vector<Vector> vertices_b = b->get_vertices();
    vector<Vector> normals_a  = a->get_normals();
    vector<Vector> normals_b  = b->get_normals();
    vector<Vector> normals = CollisionDetector::merge_Vector(normals_a, normals_b);
    vector<bool> overlaps;
    Vector axis_least_penetration(2);
    Vector current_normal = normals_a.at(0);
    double min_a, max_a;
    double min_b, max_b;
    double penetration_depth = -INF;

    for(size_t i = 0; i < normals.size(); i++) {

        current_normal = normals.at(i);
        min_a = vertices_a.at(0).dot(current_normal);
        max_a = min_a;
        min_b = vertices_b.at(0).dot(current_normal);
        max_b = min_b;

        for(size_t j = 1; j < vertices_a.size(); j++) {
            double scalar_projection = vertices_a.at(j).dot(current_normal);

            if(scalar_projection < min_a)
                min_a = scalar_projection;
            if(scalar_projection > max_a)
                max_a = scalar_projection;
        }

        for(size_t j = 1; j < vertices_b.size(); j++) {
            double scalar_projection = vertices_b.at(j).dot(current_normal);

            if(scalar_projection < min_b)
                min_b = scalar_projection;
            if(scalar_projection > max_b)
                max_b = scalar_projection;
        }

        double test_1 = min_b - max_a;
        double test_2 = min_a - max_b;

        if(!(test_1 > 0.0) && !(test_2 > 0.0)) {
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
    Vector axis_normalized = axis_least_penetration.normalize() * -penetration_depth;

    return make_pair(collision, axis_normalized);
}

/**
    Finds the contact point of the collision
    between object a and object b

    @param: Objects involved in collision,
            and collision axis of penetration
    @return: Contact point
*/
vector<Vector> CollisionDetector::get_contact_points(Object *a, Object *b, Vector axis) {
    Vector axis_n = axis.normalize();

    vector<Vector> vertices_a = a->get_vertices();
    vector<Vector> vertices_b = b->get_vertices();

    /* Find best edges of a and b */
    pair<Vector, Vector> edge_a = a->get_best_edge(axis_n);
    pair<Vector, Vector> edge_b = b->get_best_edge(axis_n  * -1);

    Vector vec_a = get<1>(edge_a) - get<0>(edge_a);  
    Vector vec_b = get<1>(edge_b) - get<0>(edge_b);

    pair<Vector, Vector> ref = make_pair(Vector(2), Vector(2));
    pair<Vector, Vector> inc = make_pair(Vector(2), Vector(2));

    /* Find the reference edge */
    bool flip = false;
    if(abs(vec_a.dot(axis_n)) <= abs(vec_b.dot(axis_n))) {
        ref = edge_a;
        inc = edge_b;
    }
    else {
        ref = edge_b;
        inc = edge_a;
        flip = true;
    }

    /* First clipping operation */
    // TODO: get precomputed normal instead
    Vector v1_inc    = get<0>(inc);
    Vector v2_inc    = get<1>(inc);
    Vector v1_ref    = get<0>(ref);
    Vector v2_ref    = get<1>(ref);
    Vector ref_vec_n = (v2_ref - v1_ref).normalize();
    Vector ref_normal(ref_vec_n.at(1), -ref_vec_n.at(0));
    ref_normal.normalize();

    double offset    = ref_vec_n.dot(v1_ref); 

    vector<Vector> clipped_points = CollisionDetector::clip(v1_inc, v2_inc,
                                                            ref_vec_n, offset);

    if(clipped_points.size() < 2)
        Display::error("Clipping #1 failed");

    /* Second clipping operation */
    offset = ref_vec_n.dot(v2_ref);
    clipped_points = CollisionDetector::clip(clipped_points.at(0),
                                             clipped_points.at(1),
                                             ref_vec_n * -1, -offset);
    
    if(clipped_points.size() < 2)
        Display::error("Clipping #2 failed");

    double depth_1   = ref_normal.dot(clipped_points.at(0) - v1_ref);
    double depth_2   = ref_normal.dot(clipped_points.at(1) - v1_ref);
    double max_depth = (depth_1 > depth_2) ? depth_1 : depth_2;

    if(depth_1 > 0.0)
        clipped_points.erase(clipped_points.begin());
    if(depth_2 > 0.0)
        clipped_points.erase(clipped_points.end());
        
    return clipped_points;
}

/**
    Clips the incident edge's vertices along the
    reference edge, given the offset

    @param Incident vertices, normalized reference vector,
            offset from where to start clipping
    @return Contact points
*/
vector<Vector> CollisionDetector::clip(Vector v1, Vector v2, Vector n, double offset) {
    vector<Vector> clipped_points;    
    
    double d1 = n.dot(v1) - offset;
    double d2 = n.dot(v2) - offset;

    if(d1 >= 0.0) clipped_points.push_back(v1);
    if(d2 >= 0.0) clipped_points.push_back(v2);

    if(d1 * d2 < 0.0) {
        Vector e = v2 - v1;
        double slope = d1 /(d1 - d2);
        e = e * slope;
        e = e + v1;
        clipped_points.push_back(e);
    }

    return clipped_points;
}

/**
    Finds all collisions between any combination
    of objects with

    @param The entire world containing all objects
    @return vector of Collision pointers

*/
vector<Collision*> CollisionDetector::get_collisions(World *world) {
    
    vector<Collision*> collisions;
    vector<Object*> objects = world->get_objects();
	
	for(size_t i = 0; i < objects.size(); i++) {
		Object* object_a = objects.at(i);

		for(size_t j = 0; j < objects.size(); j++) {
			Object* object_b = objects.at(j);
			
			bool contains = CollisionDetector::collision_contains(collisions, object_a, object_b);

			if(object_b == object_a)
				break;
			if(contains)
				break;

			pair<bool, Vector> collision_status = CollisionDetector::collision_detection_SAT(object_a, object_b);

			bool has_collision  = get<0>(collision_status);
			Vector axis         = get<1>(collision_status);

			if(has_collision) {
				if(axis.dot(*object_a->get_position()) > axis.dot(*object_b->get_position())) {
					Object* temp = object_a;
					object_a = object_b;
					object_b = temp;
				}
			
				vector<Vector> contact_points = CollisionDetector::get_contact_points(object_a, object_b, axis);
				collisions.push_back(new Collision(object_a, object_b, axis, contact_points.at(0)));
			}
		}
	}
    return collisions;
}

/**
    Compute and apply the necessary separation
    between objects due to collision overlap

    @param: Collision object contains all info
*/
void CollisionDetector::compute_apply_positional_correction(Collision *collision) {

    Vector axis = *collision->get_axis();
    Object* a = collision->get_object(true);
    Object* b = collision->get_object(false);

    Vector correction_b(2);
    Vector correction_a(2);

    if(a->is_movable() && b->is_movable()) {
        correction_a = axis *  1.5;
        correction_b = axis * -1.5;
    }
    else if(a->is_movable() && !b->is_movable()) {
        correction_a = axis * 1.5;
        correction_b = Vector(0.0, 0.0);
    }
    else if(!a->is_movable() && b->is_movable()) {
        correction_a = Vector(0.0, 0.0);
        correction_b = axis * -1.0;
    }
    else if(!a->is_movable() && !b->is_movable()) {
        correction_a = Vector(0.0, 0.0);
        correction_b = Vector(0.0, 0.0);
    }

    Vector corrected_position_a = *a->get_position() + correction_a;
    Vector corrected_position_b = *b->get_position() + correction_b;
    
    a->set_position(corrected_position_a);
    b->set_position(corrected_position_b);
}
 
/**
	Appends one vector to another

	@param vector to append to
	@param vector to append
	@return merged vector
*/
vector<Vector> CollisionDetector::merge_Vector(vector<Vector> vectors_a, vector<Vector> vectors_b) {
    vector<Vector> output;
    output = vectors_a;

    for(size_t i = 0; i < vectors_b.size(); i++)
        output.push_back(vectors_b.at(i));

    return output;
}

bool CollisionDetector::collision_contains(vector<Collision*> collisions, Object* obj_1, Object* obj_2) {
	bool contains = false;

	for(size_t k = 0; k < collisions.size(); k++) {
		if((obj_1 == collisions.at(k)->get_object(true)   ||
			obj_1 == collisions.at(k)->get_object(false)) &&
			(obj_2 == collisions.at(k)->get_object(true)   ||
			obj_2 == collisions.at(k)->get_object(false)))   {
			contains = true;	
		}
	}
	return contains;
}
