#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

class Vector;
class Object;

class Collision {
private:
	Object *object_1;
	Object *object_2;
	std::vector<Vector> contact_points;
	Vector *axis_of_penetration;
	double penetration_depth;
public:
	Collision(Object *object_1, Object *object_2);
	~Collision();

	std::vector<Vector> get_contact_points() const;
};

#endif
