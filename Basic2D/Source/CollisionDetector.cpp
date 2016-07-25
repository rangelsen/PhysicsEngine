#include <stdio.h>
#include <vector>
#include <iostream>

#include "CollisionDetector.h"
#include "Vector.h"
#include "Object.h"
#include "World.h"
#include "Collision.h"

#define INF 100000

using namespace std;

vector<Collision> CollisionDetector::find_collisions(World *world) {

    vector<Collision> collisions;

    vector<Object*> objects = world->get_objects();

    for(unsigned int i = 0; i < objects.size(); i++) {

        if(i < objects.size() - 1) {

            for(unsigned int j = i + 1; j < objects.size(); j++) {

                Vector axis_of_least_penetration = CollisionDetector::collision_detection_SAT(objects.at(i), objects.at(j));

                if(!(axis_of_least_penetration == Vector(0, 0))) {

                    Collision collision(objects.at(i), objects.at(j), axis_of_least_penetration);

                    collisions.push_back(collision);
                }
            }
        }
    }
}

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

    bool collision = (overlaps.size() == normals.size()) ? true : false;

    if(collision) {
        if(axis_least_penetration.norm() != 1)
            axis_least_penetration.normalize();

        return axis_least_penetration * penetration_depth;
    }
    else{
        return Vector(0, 0);
    }
}

vector<Vector> CollisionDetector::merge_Vector(vector<Vector> vectors_a, vector<Vector> vectors_b) {

    vector<Vector> output;
    output = vectors_a;

    for(unsigned int i = 0; i < vectors_b.size(); i++) {

        output.push_back(vectors_b.at(i));
    }

    return output;
}