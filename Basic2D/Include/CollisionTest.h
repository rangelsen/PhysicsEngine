#ifndef COLLISION_TEST_H
#define COLLISION_TEST_H

#include <vector>

class Vector;
class Object;

class CollisionTest {

public:
	static bool collision_detection_SAT(Object *a, Object *b);
	static Vector collision_detection_contact_SAT(Object *a, Object *b);
	static Vector get_contact_point(Object *a, Object *b, Vector axis_least_penetration);
	static std::vector<Vector> merge_Vector(std::vector<Vector> vectors_a, std::vector<Vector> vectors_b);
};

#endif