#include <vector>

#include "Collision.h"
#include "Vector.h"
#include "Object.h"
#include "Display.h"

using namespace std;

Collision::Collision(Object *object_1, Object *object_2, Vector axis_of_least_penetration) : object_1(object_1), 
																							 object_2(object_2) {}

Collision::~Collision() {}

vector<Vector> Collision::get_contact_points() const {
	vector<Vector> output;
	output.push_back(Vector(2, 3));
	return output;
}