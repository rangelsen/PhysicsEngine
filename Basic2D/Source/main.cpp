#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <cmath>

#include "Matrix.h"
#include "Vector.h"
#include "Constants.h"
#include "Display.h"
#include "Object.h"
#include "World.h"
#include "EOMSolver.h"
#include "Scene.h"
#include "CollisionDetector.h"
#include "object_generation.h"
#include "Collision.h"

using namespace std;

World *world;

clock_t clocks_0 = 0;
clock_t clocks_1;
unsigned int delta_time_ms = 10;
double delta_time = delta_time_ms/1000.0;
float elapsed_ms;

void run() {

	clocks_1 = clock();
	elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

	if(elapsed_ms >= delta_time_ms) {
		clocks_0 = clocks_1;

		// Find collisions
		vector<Collision*> collisions = CollisionDetector::get_collisions(world);

		// Simulate
		EOMSolver::simulate_world(world, delta_time, collisions);

		// Render
		Scene::render_world(world, collisions);

		collisions.clear();
	/* -----------------------------------------------------------------------------------------

		Vector axis_least_penetration = CollisionDetector::collision_detection_contact_SAT(world->get_objects().at(0), world->get_objects().at(1));
		
		if(axis_least_penetration == Vector(0, 0)) {

			for(unsigned int object_index = 0; object_index < world->get_objects().size(); object_index++) {
				
				Object *object = world->get_objects().at(object_index);

				EOMSolver::simulate_object(object, delta_time);
			}
		}
		else {

			Object *object_a = world->get_objects().at(0);
			Object *object_b = world->get_objects().at(1);

			Vector contact_point = CollisionDetector::get_contact_point(object_a, object_b, axis_least_penetration * -1);

			if(!flag) {
				Display::vector(axis_least_penetration, BLUE);
				flag = true;
			}

			Scene::render_contact_point(contact_point);
		}
		
		Scene::render_world(world);

	------------------------------------------------------------------------------------------- */

	}
}

int main(int argc, char** argv) {
	vector<Object*> objects = generate_objects();

	objects.at(0)->set_position(Vector(0, 4));
	objects.at(0)->set_velocity(Vector(0, 0));

	objects.at(1)->set_movable(false);
	objects.at(1)->set_position(Vector(0, -8));

	world = new World(objects);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    // glutKeyboardFunc(keyboard);
    glutIdleFunc(run);
    glutMainLoop();

 	delete world;

	return 0;
}