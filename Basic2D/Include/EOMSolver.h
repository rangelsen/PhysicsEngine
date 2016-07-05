#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

class Object;
class Vector;
class Collision;

class EOMSolver {

public:
	static void simulate_object(Object *object, std::vector<Collision*> collisions, double time_step);
	static Vector evaluate_forces(Object *object, std::vector<Collision*> collisions);
};

#endif