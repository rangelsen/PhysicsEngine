#include <stdio.h>
#include <vector>

#include "EOMSolver.h"
#include "World.h"
#include "Object.h"
#include "Display.h"
#include "Object.h"
#include "Constants.h"
#include "Vector.h"

using namespace std;

void EOMSolver::resolve_time_step(World &world, unsigned int time_step) {
	vector<Object*> objects = world.get_objects();
	for(int i = 0; i < objects.size(); i++) {
		EOMSolver::simulate_object(*objects.at(i), time_step);

		Display::vector(objects.at(i)->get_state(), RED);
	}
	printf("--------------\n");
}

void EOMSolver::simulate_object(Object &object, unsigned int time_step) {
	Vector x_0 = object.get_state();
	Vector d_x = EOMSolver::evaluate_object_EOM(object);
	double t = 1/time_step;
	Vector x_1 = x_0 + d_x * t;

	object.set_state(x_1);
}

Vector EOMSolver::evaluate_object_EOM(Object &object) {
	Vector B("zeros", 6);
	B.at(3) = -Constants::Instance()->g;


	Vector f = *Constants::Instance()->A * object.get_state() + B;
	return f;
}
