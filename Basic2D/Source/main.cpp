#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "World.h"
#include "EOMSolver.h"
#include "Object.h"
#include "Matrix.h"
#include "Display.h"
#include "Vector.h"

using namespace std;

void Run(World *world) {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	unsigned int delta_time = 200;
	float elapsed_ms;

	while(true) {
		clocks_1 = clock();
		elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

		if(elapsed_ms >= delta_time) {
			clocks_0 = clocks_1;

			// Do computations
			EOMSolver::resolve_time_step(world, delta_time);
		}
	}
}

vector<Object*> generate_objects(int n_objects, int n_vertices) {

	vector<Object*> objects;
	vector<Vector*> vertices;

	srand(time(NULL));

	for(int i = 0; i < n_objects; i++) {
		vertices.clear();

		for(int j = 0; j < n_vertices; j++) {
			Vector *vertex = new Vector(rand() % 20 + 1, rand() % 20 + 1);
			vertices.push_back(vertex);
		}
		Object *object = new Object(vertices);
		objects.push_back(object);
	}

	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(3, 3);

	Display::object(objects.at(0), WHITE);
	Display::object(objects.at(1), WHITE);

	World *world = new World(objects);

	Run(world);

	return 0;
}