#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>

#include "Matrix.h"
#include "Vector.h"
#include "Constants.h"
#include "Display.h"
#include "Object.h"
#include "World.h"
#include "EOMSolver.h"
#include "Scene.h"
#include "Collision.h"
#include "CollisionDetector.h"

using namespace std;

World *world;

clock_t clocks_0 = 0;
clock_t clocks_1;
unsigned int delta_time_ms = 10;
double delta_time = delta_time_ms/1000.0;
float elapsed_ms;
int count = 0;

void run() {

	clocks_1 = clock();
	elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

	if(elapsed_ms >= delta_time_ms) {
		clocks_0 = clocks_1;

		vector<Collision*> collisions = CollisionDetector::SAT_detect_collisions(world);

		for(unsigned int object_index = 0; object_index < world->get_objects().size(); object_index++) {

			EOMSolver::simulate_object(world->get_objects().at(object_index), collisions, delta_time);
		}

		Scene::render_world(world, collisions);

		for(unsigned int i = 0; i < collisions.size(); i++) {
			delete collisions.at(i);
		}
	}
}

vector<Object*> generate_objects(unsigned int n_objects, unsigned int n_vertices) {
	vector<Object*> objects;
	vector<Vector> vertices;

	srand(time(NULL));
	
	for(int i = 0; i < n_objects; i++) {
		vertices.clear();
		for(int j = 0; j < n_vertices; j++) {
			Vector vertex(rand() % 6 + 2, rand() % 6 + 2);
			vertices.push_back(vertex);
		}

		Object *object = new Object(vertices);
		objects.push_back(object);
	}

	vertices.clear();

	double width = 10;
	double height = 1;

	Vector v1(-width/2.0, height/2.0);
	Vector v2(width/2.0, height/2.0);
	Vector v3(-width/2.0, -height/2.0);
	Vector v4(width/2.0, -height/2.0);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v4);
	vertices.push_back(v3);

	Object *object = new Object(vertices);
	object->set_movable(false);
	object->set_position(Vector(0, -8));
	objects.push_back(object);

	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(1, 3);

	objects.at(0)->set_position(Vector(-4, 3));
	objects.at(0)->set_velocity(Vector(1.5, 8));

	world = new World(objects);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    glutIdleFunc(run);
    glutMainLoop();
 	delete world;

	return 0;
}