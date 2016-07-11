#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>

class World;
class Vector;

class CollisionDetector {

public:
	static std::vector<Vector> SAT_detect_collisions(World *world);
	static std::vector<Vector> merge_normals(std::vector<Vector> normals_a, std::vector<Vector> normals_b);
};

#endif