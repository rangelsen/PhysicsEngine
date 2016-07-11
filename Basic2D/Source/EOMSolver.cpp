#include <stdio.h>
#include <vector>

#include "EOMSolver.h"
#include "Object.h"
#include "Display.h"
#include "Object.h"
#include "Constants.h"
#include "Vector.h"
#include "Collision.h"

using namespace std;

void EOMSolver::simulate_object(Object *object, double delta_time) {

	if(object->is_movable()) {

		double inv_inertia = 1.0/object->get_moment_of_inertia();

		double torque = EOMSolver::evaluate_torque(object);

		double next_d_theta = object->get_rotation() + torque * inv_inertia * delta_time;

		double next_theta = object->get_orientation() + next_d_theta * delta_time;

		// -----------------------------------------------------------------------------

		double inv_mass = 1.0/object->get_mass();

		Vector f = EOMSolver::evaluate_forces(object);

		Vector next_velocity = *object->get_velocity() + f * inv_mass * delta_time;
		
		Vector next_position = *object->get_position() + next_velocity * delta_time;

		object->set_velocity(next_velocity);
		object->set_position(next_position);
		object->set_orientation(next_theta);
	}
}

Vector EOMSolver::evaluate_forces(Object *object) {
	
	return Vector(0, -object->get_mass() * Constants::Instance()->g);
}

double EOMSolver::evaluate_torque(Object *object) {

	return 1;
}
