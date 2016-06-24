#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "World.h"
#include "EOMSolver.h"
#include "Matrix.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

void Run(World &world) {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	unsigned int delta_time = 500;
	float elapsed_ms;

	EOMSolver solver;

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

vector<Object> generate_objects(unsigned int n_objects, unsigned int n_vertices) {
	vector<Object> objects;
	vector<Vector> vertices;

	Vector vertex1(2, 1);
	Vector vertex2(5, 8);
	Vector vertex3(5, 1);

	vertices.push_back(vertex1);
	vertices.push_back(vertex2);
	vertices.push_back(vertex3);

	Object object(vertices);

	objects.push_back(object);
	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(3, 2);

	return 0;
}