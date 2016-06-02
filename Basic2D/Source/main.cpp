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

	Matrix *vertices = new Matrix[2];

	vertices = new Matrix(2, 2);

	vertices[0].print_console();

	delete vertices;

	return 0;
}