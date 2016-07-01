#include <stdio.h>
#include <vector>
#include <iostream>

#include "EOMSolver.h"
#include "World.h"
#include "Object.h"
#include "Display.h"
#include "Object.h"
#include "Constants.h"
#include "Vector.h"

using namespace std;

// #define DEBUG

#ifdef DEBUG
#define Debug(x) cout << x
#else
#define Debug(x) 
#endif 

void EOMSolver::resolve_time_step(World &world, double delta_time) {
	vector<Object*> objects = world.get_objects();
	for(int i = 0; i < objects.size(); i++) {
		EOMSolver::simulate_object(*objects.at(i), delta_time);

	}
	// Debug("----------------------------------------" << endl);
}

void EOMSolver::simulate_object(Object &object, double delta_time) {
	double inv_mass = 1.0/Constants::Instance()->mass;

	Vector f = EOMSolver::evaluate_forces(object, delta_time) * inv_mass;

	Vector next_velocity = *object.get_velocity() + f * delta_time;
	
	Vector next_position = *object.get_position() + next_velocity * delta_time;
	// Display::vector(next_position, MAGENTA);
	// Display::vector(next_velocity, MAGENTA);

	object.set_velocity(next_velocity);
	object.set_position(next_position);
}

Vector EOMSolver::evaluate_forces(Object &object, double delta_time) {
	
	return Vector(0, Constants::Instance()->mass * (-Constants::Instance()->g));
}
