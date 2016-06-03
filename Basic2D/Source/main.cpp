#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "World.h"
#include "PhysicsSolver.h"
#include "Object.h"
#include "Matrix.h"
#include "Display.h"

using namespace std;

void Run(World *world) {

	clock_t clocks_0 = 0;
	clock_t clocks_1;
	int delta_time = 200;
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

vector<Object*> generate_objects(int n_objects, int n_vertices) {

	vector<Object*> objects;
	vector<Matrix*> vertices;
/*
	for(int n = 0; n < n_objects; n++) {
		
		vertices.clear();

		for(int i = 0; i < n_vertices; i++) {

			Matrix *vertex = new Matrix(2, 1);
			vertex->set(0, 0, rand() % 20 + 1);
			vertex->set(1, 0, rand() % 20 + 1);

			vertices.push_back(vertex);
		}

		Object *object = new Object(vertices);
		objects.push_back(object);
	}
*/

	Matrix *v1 = new Matrix(2, 1);
	v1->set(0, 0, -1);
	v1->set(1, 0, 1);
	vertices.push_back(v1);

	Matrix *v2 = new Matrix(2, 1);
	v2->set(0, 0, 1);
	v2->set(1, 0, 1);
	vertices.push_back(v2);

	Matrix *v3 = new Matrix(2, 1);
	v3->set(0, 0, 1);
	v3->set(1, 0, -1);
	vertices.push_back(v3);

	Matrix *v4 = new Matrix(2, 1);
	v4->set(0, 0, -1);
	v4->set(1, 0, -1);
	vertices.push_back(v4);

	Object *object = new Object(vertices);
	objects.push_back(object);

	return objects;
}

int main(int argc, char** argv) {

	vector<Object*> objects = generate_objects(2, 4);

	vector<float> centroids = objects.at(0)-> calculate_centroid();

	printf("centroids: %f, %f\n", centroids.at(0), centroids.at(1));
	// World *world = new World(objects);
	// Run(world);
	return 0;
}