#include <stdio.h>
#include <vector>

#include "EOMSolver.h"
#include "World.h"
#include "Vector.h"
#include "Constants.h"

using namespace std;

void EOMSolver::resolve_time_step(World &world, unsigned int time_step) {
	printf("Resolving step\n");
/*
	vector<Object*> objects = world.get_objects();

	for(int i = 0; i < objects.size(); i++) {
		EOMSolver::simulate_object(objects.at(i), time_step);
	}
*/
}

/*
void EOMSolver::simulate_object(Object *object, unsigned int time_step) {
	Vector v = compute_EOM_object(object);
}

Vector EOMSolver::compute_EOM_object(Object *object) {
	Vector dx_1 = object->get_velocity();
	Vector dx_2 = object->get_velocity() * 2;

	Vector output(4);
	output.set(1, dx_1[1]);
	return output;
}
*/