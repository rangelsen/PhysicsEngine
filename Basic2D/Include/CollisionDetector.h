#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>

class Collision;
class World;

class CollisionDetector {

public:
	static std::vector<Collision*> SAT_detect_collisions(World *world);
};
#endif