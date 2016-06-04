#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

class World;

class EOMSolver {
private:
public:
	static void resolve_time_step(World *world, unsigned int delta_time);
};

#endif