#include <iostream>
#include <time.h>
#include "World.h"
#include "PhysicsSolver.h"
#include "Object.h"

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

	World *world = new World();
	world->add_object(new Object());

	printf("Number of objects in world: %d\n", world->get_number_of_objects());

	Run(world);

	return 0;
}