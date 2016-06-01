#ifndef PHYSICS_SOLVER_H
#define PHYSICS_SOLVER_H

class World;

class PhysicsSolver {
private:
public:
	static void resolveTimeStep(World *world, int delta_time);
};

#endif