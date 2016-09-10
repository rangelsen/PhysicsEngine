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

using namespace std;

void EOMSolver::simulate_world(World *world, double time_step, vector<Collision*> collisions, ofstream& theta_file, ofstream& d_theta_file) {

	vector<Object*> objects = world->get_objects();

	for(unsigned int i = 0; i < objects.size(); i++) {

		vector<Collision*> related_collisions = EOMSolver::get_related_collisions(objects.at(i), collisions);

		EOMSolver::simulate_object(objects.at(i), time_step, related_collisions, theta_file, d_theta_file);
	}
}

void EOMSolver::simulate_object(Object *object, double delta_time, vector<Collision*> related_collisions, ofstream& theta_file, ofstream& d_theta_file) {

	if(object->is_movable()) {

		double inv_mass = 1.0f/object->get_mass();
		double inv_intertia = 1.0f/object->get_moment_of_inertia();

		Vector next_velocity = object->get_velocity();
		double next_angular_velocity = object->get_angular_velocity();

		for(unsigned int i = 0; i < related_collision.size(); i++) {

			Collision *current_collision = related_collision.at(i);

			Vector impulse = EOMSolver::compute_impulse(object, current_collision, double delta_time);

			Vector r = current_collision->get_contact_point() - object->get_position();

			next_velocity         += impulse * inv_mass;
			next_angular_velocity += object->get_angular_velocity() + impulse.cross2D(r) * inv_inertia;
		}

		Vector next_position = *object->get_position() + next_velocity * delta_time;
		double next_orientation      = object->get_orientation() + object->get_angular_velocity() * delta_time;

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

double EOMSolver::compute_impulse(Object *a, vector<Collision*> related_collisions, double delta_time) {

	double impulse = 0;

	for(unsigned int i = 0; i < related_collisions.size(); i++) {

		Object *b = related_collisions.at(i)->get_object(false);

		if(b == a)
			b = related_collisions.at(i)->get_object(true);

		Vector n = *related_collisions.at(i)->get_axis();

		Vector r_a = *related_collisions.at(i)->get_contact_point() - *a->get_position();
		Vector r_b = *related_collisions.at(i)->get_contact_point() - *b->get_position();

		Vector v_ap1 = *a->get_velocity() + Vector(-r_a.at(1), r_a.at(0)) * a->get_angular_velocity();
		Vector v_bp1 = *b->get_velocity() + Vector(-r_b.at(1), r_b.at(0)) * b->get_angular_velocity();

		Vector v_ab = v_ap1 - v_bp1;

		double num = -(1 + Constants::Instance()->elasticity) * v_ap1.dot(n);

		double inv_mass_a = 1/a->get_mass();

		double r_cross_n_a = r_a.cross2D(n);

		double rot_term_a = r_cross_n_a * r_cross_n_a / a->get_moment_of_inertia();

		double den = inv_mass_a + rot_term_a;

		impulse = num / den;

		if(r_cross_n_a < 0)
			impulse *= -1;
		
	}

	return impulse;
}
