#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "EOMSolver.h"
#include "Object.h"
#include "Display.h"
#include "Object.h"
#include "Constants.h"
#include "Vector.h"
#include "Collision.h"
#include "World.h"
#include "CollisionDetector.h"

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
        double inv_inertia = 1.0f/object->get_moment_of_inertia();

        Vector next_velocity = *object->get_velocity();
        double next_angular_velocity = object->get_angular_velocity();

        for(unsigned int i = 0; i < related_collisions.size(); i++) {
            Collision *current_collision = related_collisions.at(i);
            CollisionDetector::compute_apply_positional_correction(object, current_collision);
            
            Vector impulse        = EOMSolver::compute_impulse(object, current_collision);
            Vector r              = *current_collision->get_contact_point() - *object->get_position();
            next_velocity         += impulse * inv_mass;
            next_angular_velocity += r.cross2D(impulse) * inv_inertia;
        }

        Vector gravity(0, -Constants::Instance()->g);
        next_velocity +=  gravity * delta_time;

        Vector next_position    = *object->get_position() + next_velocity * delta_time;
        double next_orientation = object->get_orientation() + object->get_angular_velocity() * delta_time;

        object->set_velocity(next_velocity);
        object->set_position(next_position);

        object->set_angular_velocity(next_angular_velocity);
        object->set_orientation(next_orientation);
    }	
}

Vector EOMSolver::evaluate_forces(Object *object, vector<Collision*> related_collisions, double delta_time) {
	
	Vector f(0, 0);
	double inv_time = 1.0f/delta_time;

	for(unsigned int i = 0; i < related_collisions.size(); i++) {
		
		Vector correction = *object->get_position() + *related_collisions.at(i)->get_axis();

		object->set_position(correction);

		f += *object->get_velocity() * (-Constants::Instance()->restitution - 1) * object->get_mass() * inv_time + Vector(0, 0);
	}

	return f;
}

double EOMSolver::evaluate_torque(Object *object, Vector force, vector<Collision*> related_collisions, double delta_time) {
  	double t = 0;
  	double inv_time = 1.0f/delta_time;
  
 	for(unsigned int i = 0; i < related_collisions.size(); i++) {

 		Vector arm = *related_collisions.at(i)->get_contact_point() - *object->get_position();

 		// double h = object->get_velocity()->cross2D(arm);
 		double h = arm.cross2D(*object->get_velocity());
 		t += h * delta_time;

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

// Returns the impulse vector that the given collision contributes to object a
Vector EOMSolver::compute_impulse(Object *a, Collision *collision) {

	Vector impulse(0, 0);

	Object *b = collision->get_object(false);

	if(b == a) {
		b = collision->get_object(true);
	}

	Vector n = *collision->get_axis();

	Vector r_a = *collision->get_contact_point() - *a->get_position();
	Vector r_b = *collision->get_contact_point() - *b->get_position();

	Vector v_ap1 = *a->get_velocity() + Vector(-r_a.at(1), r_a.at(0)) * a->get_angular_velocity();
	Vector v_bp1 = *b->get_velocity() + Vector(-r_b.at(1), r_b.at(0)) * b->get_angular_velocity();

	Vector v_ab = v_ap1 - v_bp1;

	double num = -(1 + Constants::Instance()->restitution) * v_ap1.dot(n.normalize());

	double inv_mass_a = 1/a->get_mass();

	double r_cross_n_a = r_a.cross2D(n.normalize());

	double rot_term_a = r_cross_n_a * r_cross_n_a / a->get_moment_of_inertia();

	double den = inv_mass_a + rot_term_a;

	double impulse_scalar = num / den;

	impulse = collision->get_axis()->normalize() * impulse_scalar;

	return impulse;
}
