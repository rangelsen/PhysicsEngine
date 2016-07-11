#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

class Object;
class Vector;
class Collision;

class EOMSolver {

public:
	static void simulate_object(Object *object, double time_step);
	static Vector evaluate_forces(Object *object);
};

#endif