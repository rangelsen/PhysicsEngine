#include <stdio.h>
#include <time.h>
#include <iostream>

#include "World.h"
#include "PhysicsSolver.h"
#include "Object.h"
#include "Matrix.h"

using namespace std;

void Run(World *world) {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	int delta_time = 500;
	float elapsed_ms;

	while(true) {

		clocks_1 = clock();
		elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

		if(elapsed_ms >= delta_time) {
			clocks_0 = clocks_1;

			// Do computations
			PhysicsSolver::resolveTimeStep(world, delta_time);
		}
	}
}

int main(int argc, char** argv) {

	int vertex_count = 4;
	Matrix **vertices = new Matrix*[vertex_count];

	for(int i = 0; i < vertex_count; i++) {

		vertices[i] = new Matrix(2, 1);
		vertices[i]->set(0, 0, rand() % 20 + 1);
		vertices[i]->set(1, 0, rand() % 20 + 1);

		vertices[i]->print_console();
	}

	delete[] vertices;

	return 0;
}