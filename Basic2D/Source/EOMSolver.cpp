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
	double inv_mass = 1.0/object.get_mass();

	Vector f = EOMSolver::evaluate_forces(object);

	Vector next_velocity = *object.get_velocity() + f * inv_mass * delta_time;
	
	Vector next_position = *object.get_position() + next_velocity * delta_time;

	object.set_velocity(next_velocity);
	object.set_position(next_position);
}

Vector EOMSolver::evaluate_forces(Object &object) {
	
	return Vector(0, -object.get_mass() * Constants::Instance()->g);
}
