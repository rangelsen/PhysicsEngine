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

/**
	Resolves all collision in the given world

	@param world in which collision takes place
	@param collection of collisions in given world
	@param simulation time step
*/
void EOMSolver::resolve_collisions(World* world, vector<Collision*> collisions, double time_step) {
	
	for(size_t i = 0; i < collisions.size(); i++) {
		Collision* collision = collisions.at(i);
		Object* a = collision->get_object(true);
		Object* b = collision->get_object(false);

		// TODO: Error when multiple objects collide with an object at the same time
		Vector contact_point = *collision->get_contact_point();

		/* Separate objects */
		CollisionDetector::compute_apply_positional_correction(collision);
		
		/* Compute impulse */
		Vector impulse(2);
		if(a->is_movable() && b->is_movable())
			impulse = EOMSolver::compute_impulse_two(collision);
		else
			impulse = EOMSolver::compute_impulse(collision);
		
		/* Apply impulse */
		EOMSolver::apply_impulse(a, impulse*1.0, contact_point, time_step); 
		EOMSolver::apply_impulse(b, impulse*-1.0, contact_point, time_step); 
	}
	
	vector<Object*> objects = world->get_objects();
	for(size_t i = 0; i < objects.size(); i++) {
		EOMSolver::step(objects.at(i), time_step);
	}
}

/**
	Applies the impulse vector to the object in
	order to generate the next angular and linear
	velocities

	@param the object the impulse is applied to
	@param the impulse vector
	@param the contact point where the
		   impulse occurred
	@param the size of the time step	
*/
void EOMSolver::apply_impulse(Object* object, Vector impulse, Vector contact_point, double time_step) {
	/* Early out if object is non-movable */
	if(!object->is_movable())
		return;

	double inv_mass    			 = 1.0/object->get_mass();
	double inv_inertia 			 = 1.0/object->get_moment_of_inertia();
	Vector r               		 = contact_point - *object->get_position();
	double next_angular_velocity = object->get_angular_velocity() + r.cross2D(impulse) * inv_inertia;
	Vector next_velocity 		 = *object->get_velocity() + Vector(0, -Constants::Instance()->g) * time_step;
	next_velocity        		+= impulse * inv_mass;

	object->set_velocity(next_velocity);
	object->set_angular_velocity(next_angular_velocity);
}

/**
	Uses Euler's direct integration scheme
	to compute the new position and orientation
	of the object

	@param the object for which to compute the updates
	@param the time step of integration	
*/
void EOMSolver::step(Object* object, double time_step) {
	/* Early out if object is non-movable */
	if(!object->is_movable())
		return;

	Vector gravity_vel_contrib = *object->get_velocity() + Vector(0, -Constants::Instance()->g) * time_step;
	object->set_velocity(gravity_vel_contrib);

	Vector next_position    = *object->get_position()   + *object->get_velocity()		 * time_step;
	double next_orientation = object->get_orientation() + object->get_angular_velocity() * time_step;

	object->set_position(next_position);
	object->set_orientation(next_orientation);
}

/**
    Returns the impulse vector that the
    given collision contributes to object a

    @param: Collision between objects
    @return: Impulse vector
*/
Vector EOMSolver::compute_impulse(Collision *collision) {
    Object *a = collision->get_object(true);
    Object *b = collision->get_object(false);

    Vector n      = *collision->get_axis();
	Vector n_norm = n.normalize();
    Vector r_a    = *collision->get_contact_point() - *a->get_position();
    Vector r_b    = *collision->get_contact_point() - *b->get_position();
    Vector v_ap1  = *a->get_velocity() + r_a.cross2D(a->get_angular_velocity());
    Vector v_bp1  = *b->get_velocity() + r_b.cross2D(b->get_angular_velocity()); // Vector(-r_b.at(1), r_b.at(0)) * b->get_angular_velocity();
    Vector v_ab1  = v_ap1 - v_bp1;
	
    double num            = -(1 + Constants::Instance()->restitution) * v_ab1.dot(n_norm);
    double inv_mass_a     = 1/a->get_mass();
    double r_cross_n_a    = r_a.cross2D(n_norm);
    double rot_term_a     = r_cross_n_a * r_cross_n_a / a->get_moment_of_inertia();
    double den            = inv_mass_a + rot_term_a;
    double impulse_scalar = num / den;

    Vector impulse(2);
    impulse = n_norm * impulse_scalar;

    return impulse;
}

/**
	Computes impulse based on collision between
	two movable objects with finite mass

	@param collision object containing all collision info
	@return Impulse vector (not sure on which
		    object this is to be applied)

*/
Vector EOMSolver::compute_impulse_two(Collision *collision) {
    Object *a = collision->get_object(true);
    Object *b = collision->get_object(false);

    Vector n      = *collision->get_axis();
    Vector n_norm = n.normalize(); 
    Vector r_ap   = *collision->get_contact_point() - *a->get_position();
    Vector r_bp   = *collision->get_contact_point() - *b->get_position();
    Vector v_ap1  = *a->get_velocity() + r_ap.cross2D(a->get_angular_velocity());
    Vector v_bp1  = *b->get_velocity() + r_bp.cross2D(b->get_angular_velocity());
    Vector v_ab1   = v_ap1 - v_bp1;

    double inv_mass_a = 1.0/a->get_mass();
    double inv_mass_b = 1.0/b->get_mass();

    double num         = -(1.0 + Constants::Instance()->restitution) * v_ab1.dot(n_norm);
    double r_cross_n_a = r_ap.cross2D(n_norm);
    double r_cross_n_b = r_bp.cross2D(n_norm);
    double rot_term_a  = r_cross_n_a * r_cross_n_a / a->get_moment_of_inertia();
    double rot_term_b  = r_cross_n_b * r_cross_n_b / b->get_moment_of_inertia();
    double den         = inv_mass_a + inv_mass_b + rot_term_a + rot_term_b;
    double impulse_mag = num / den;

    Vector impulse = n_norm * impulse_mag;
    return impulse;
}

