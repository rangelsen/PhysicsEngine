#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

class Vector;
class Object;

class Collision {
private:
	Object *object_a;
	Object *object_b;
	Vector *contact_point;
	Vector *axis;

public:
	Collision(Object *object_a, Object *object_b, Vector axis_least_penetration, Vector contact_point);
	~Collision();

	Object * get_object(bool a) const;
	Vector * get_contact_point() const;
};

#endif
