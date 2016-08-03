#include <vector>

#include "Collision.h"
#include "Vector.h"
#include "Object.h"
#include "Display.h"

using namespace std;

Collision::Collision(Object *object_a, Object *object_b, Vector axis_least_penetration, Vector contact_point) {
	this->object_a = object_a;
	this->object_b = object_b;

	this->axis = new Vector(axis_least_penetration.at(0), axis_least_penetration.at(1));

	this->contact_point = new Vector(contact_point.at(0), contact_point.at(1));
}

Collision::~Collision() {
	delete this->axis;
	delete this->contact_point;
}

Object * Collision::get_object(bool a) const {

	if(a)
		return this->object_a;
	else
		return this->object_b;
}

Vector * Collision::get_contact_point() const {
	return this->contact_point;
}