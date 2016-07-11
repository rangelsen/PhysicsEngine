#ifndef COLLISION_TEST_H
#define COLLISION_TEST_H

class Vector;
class Object;

class CollisionTest {

public:
	static Vector collision_detection_SAT(Object *a, Object *b);
};

#endif