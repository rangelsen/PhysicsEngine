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

	}
	printf("----------------------------------------\n");
}

void EOMSolver::simulate_object(Object &object, unsigned int time_step) {
	double inv_mass = 1/Constants::Instance()->mass;
	double dt = 1/time_step;

	Vector a = EOMSolver::evaluate_forces(object, time_step) * inv_mass;

	Vector next_velocity = *object.get_velocity() + a * dt;	
	Display::vector(next_velocity, WHITE);

	Vector next_position = *object.get_position() + next_velocity * dt;
	Display::vector(next_position, WHITE);

	object.set_velocity(next_velocity);
	object.set_position(next_position);
}

Vector EOMSolver::evaluate_forces(Object &object, unsigned int time_step) {
	
	return Vector(0, Constants::Instance()->mass * (-Constants::Instance()->g));
}
