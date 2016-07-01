#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

class World;
class Object;
class Vector;

class EOMSolver {

public:
	static void resolve_time_step(World &world, double time_step);
	static void simulate_object(Object &object, double time_step);
	static Vector evaluate_forces(Object &object, double time_step);
};

#endif