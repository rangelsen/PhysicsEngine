#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "Matrix.h"
#include "Vector.h"
#include "Constants.h"
#include "Display.h"
#include "Object.h"
#include "World.h"
#include "EOMSolver.h"

using namespace std;

void Run(World &world) {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	unsigned int delta_time = 1000;
	float elapsed_ms;

	int count = 0;
	while(count < 10) {
		clocks_1 = clock();
		elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

		if(elapsed_ms >= delta_time) {
			clocks_0 = clocks_1;

			// Do computations
			EOMSolver::resolve_time_step(world, delta_time);
			count++;
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
			Vector vertex(rand() % 20 + 1, rand() % 20 + 1);
			vertices.push_back(vertex);
		}

		Object *object = new Object(vertices);
		objects.push_back(object);
	}
	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(2, 3);

	World world(objects);

	Run(world);

	return 0;
}