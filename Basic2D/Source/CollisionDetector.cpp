#include <stdio.h>
#include <vector>
#include <iostream>

#include "CollisionDetector.h"
#include "Vector.h"
#include "Object.h"
#include "World.h"

using namespace std;

vector<Vector> CollisionDetector::SAT_detect_collisions(World *world) {

/*
	for any object
		for any of the other objects
			- find penetrating axis and depth
			- find contact points
			- move object apart from other object in direction of
			  penetrating axis with magnitude equal to the depth
*/
    vector<Vector> contact_points;

    vector<Object*> objects = world->get_objects();

    for(unsigned int i = 0; i < objects.size(); i++) {

    	for(unsigned int j = 0; j < objects.size(); j++) {

    		if(j != i) {
    			vector<Vector> normals = CollisionDetector::merge_normals(objects.at(i)->get_normals(), objects.at(j)->get_normals());

    			vector<Vector> projections_i;
    			vector<Vector> projections_j;

    			for(unsigned int n = 0; n < normals.size(); n++) {

    				for(unsigned int k = 0; k < objects.at(i)->get_vertices().size(); k++) {

    					Vector vertex = objects.at(i)->get_vertices().at(k);
    					Vector vertex_projection = vertex.project(normals.at(n));

    					projections_i.push_back(vertex_projection);
    				}

    				for(unsigned int l = 0; l < objects.at(j)->get_vertices().size(); l++) {

    					Vector vertex = objects.at(j)->get_vertices().at(l);
    					Vector vertex_projection = vertex.project(normals.at(n));

    					projections_j.push_back(vertex_projection);
    				}
    			}

                contact_points = projections_i;
    		}
    	}
    }

    return contact_points;
}

vector<Vector> CollisionDetector::merge_normals(vector<Vector> normals_a, vector<Vector> normals_b) { 
    vector<Vector> output;
    output = normals_a;

    for(unsigned int i = 0; i < normals_a.size(); i++) {

        for(unsigned int j = 0; j < normals_b.size(); j++) {

            if(!(output.at(i) == normals_b.at(j))) {
                output.push_back(normals_b.at(j));
            }
        }
    }

    return output;
}