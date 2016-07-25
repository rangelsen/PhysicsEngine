#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>

class World;
class Vector;
class Collision;
class Object;

class CollisionDetector {

public:
	static std::vector<Collision> find_collisions(World *world);
	static Vector 				  collision_detection_SAT(Object *object_a, Object *object_b);
	static std::vector<Vector>	  merge_Vector(std::vector<Vector> vectors_a, std::vector<Vector> vectors_b);
};

#endif