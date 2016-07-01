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

using namespace std;

World *world;

clock_t clocks_0 = 0;
clock_t clocks_1;
unsigned int delta_time_ms = 1500;
double delta_time = delta_time_ms/1000.0;
float elapsed_ms;
int count = 0;

void run() {

	clocks_1 = clock();
	elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

	if(elapsed_ms >= delta_time_ms) {
		clocks_0 = clocks_1;

		EOMSolver::resolve_time_step(*world, delta_time);
		Scene::render_world(world);

		count++;
		cout << delta_time * count << endl;
	}
}

vector<Object*> generate_objects(unsigned int n_objects, unsigned int n_vertices) {
	vector<Object*> objects;
	vector<Vector> vertices;

	srand(time(NULL));
	
	for(int i = 0; i < n_objects; i++) {
		vertices.clear();
		for(int j = 0; j < n_vertices; j++) {
			Vector vertex(rand() % 40 + 1, rand() % 40 + 1);
			vertices.push_back(vertex);
		}

		Object *object = new Object(vertices);
		objects.push_back(object);
	}
	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(1, 3);

	world = new World(objects);

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    glutIdleFunc(run);
    glutMainLoop();

	delete world;

	return 0;
}