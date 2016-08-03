#include <stdio.h>
#include <vector>
#include <iostream>

#include "EOMSolver.h"
#include "Object.h"
#include "Display.h"
#include "Object.h"
#include "Constants.h"
#include "Vector.h"
#include "Collision.h"
#include "World.h"

using namespace std;

void EOMSolver::simulate_world(World *world, double time_step, vector<Collision*> collisions) {

	vector<Object*> objects = world->get_objects();

	for(unsigned int i = 0; i < objects.size(); i++) {

		vector<Collision*> related_collisions = EOMSolver::get_related_collisions(objects.at(i), collisions);

		EOMSolver::simulate_object(objects.at(i), time_step, related_collisions);
	}
}

void EOMSolver::simulate_object(Object *object, double delta_time, vector<Collision*> related_collisions) {
	
	if(object->is_movable()) {

		double inv_mass = 1.0f/object->get_mass();

		Vector f = EOMSolver::evaluate_forces(object, related_collisions, delta_time);
		Vector gravity(0, -object->get_mass() * Constants::Instance()->g);

		Vector next_velocity = *object->get_velocity() + (f + gravity) * inv_mass * delta_time;
		Vector next_position = *object->get_position() + next_velocity * delta_time;

		// -----------------------------------------------------------------------------

		double inv_inertia = 1.0f/object->get_moment_of_inertia();

		double torque = EOMSolver::evaluate_torque(object, f, related_collisions);

		double next_d_theta = object->get_rotation() + torque * inv_inertia * delta_time;
		double next_theta   = object->get_orientation() + next_d_theta * delta_time;

		object->set_velocity(next_velocity);
		object->set_position(next_position);
		object->set_rotation(next_d_theta);
		object->set_orientation(next_theta);
	}	
}

Vector EOMSolver::evaluate_forces(Object *object, vector<Collision*> related_collisions, double delta_time) {
	
	Vector f(0, 0);
	double inv_time = 1.0f/delta_time;

	for(unsigned int i = 0; i < related_collisions.size(); i++) {
		
		Vector correction = *object->get_position() + *related_collisions.at(i)->get_axis();

		object->set_position(correction);

		f += *object->get_velocity() * (-Constants::Instance()->restitution - 1) * object->get_mass() * inv_time;
	}

	return f;
}

double EOMSolver::evaluate_torque(Object *object, Vector force, vector<Collision*> related_collisions) {

	double t = 0;

	for(unsigned int i = 0; i < related_collisions.size(); i++) {
		
		Vector arm = *related_collisions.at(i)->get_contact_point() - *object->get_position();

		double torque = force.cross2D(arm);

		t -= torque/50000;
	}

	return t;
}

vector<Collision*> EOMSolver::get_related_collisions(Object *object, vector<Collision*> collisions) {

	vector<Collision*> related_collisions;

	for(unsigned int i = 0; i < collisions.size(); i++) {

		if(collisions.at(i)->get_object(true) == object || collisions.at(i)->get_object(false) == object) {

			related_collisions.push_back(collisions.at(i));
		}
	}

	return related_collisions;
}
