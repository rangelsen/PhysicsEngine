#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include <fstream>

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

ofstream theta_file;
ofstream d_theta_file;

void run() {

	clocks_1 = clock();
	elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

	if(elapsed_ms >= delta_time_ms) {
		clocks_0 = clocks_1;

		// Find collisions
		vector<Collision*> collisions = CollisionDetector::get_collisions(world);

		// Simulate
		EOMSolver::simulate_world(world, delta_time, collisions, theta_file, d_theta_file);

		// Render
		Scene::render_world(world, collisions);

		collisions.clear();
	}
}

void configure_objects_vertical(vector<Object*> objects) {

	objects.at(0)->set_position(Vector(0, 4));
	objects.at(0)->set_velocity(Vector(0, 0));

	objects.at(1)->set_movable(false);
	objects.at(1)->set_position(Vector(0, -8));
}

void configure_objects_horizontal(vector<Object*> objects) {
	objects.at(0)->set_position(Vector(-3, -3));
	objects.at(0)->set_velocity(Vector(5, 6));

	objects.at(1)->set_movable(false);
	objects.at(1)->set_position(Vector(8, 0));
	objects.at(1)->set_orientation(3.14/2);
}

int main(int argc, char** argv) {
	vector<Object*> objects = generate_objects();

	configure_objects_vertical(objects);
	// configure_objects_horizontal(objects);
	
	theta_file.open("theta.txt");
	d_theta_file.open("d_theta.txt");
	world = new World(objects);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    glutIdleFunc(run);
    glutMainLoop();

 	delete world;

	return 0;
}