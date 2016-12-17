#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

#include <fstream>

class Object;
class Vector;
class Collision;
class World;

class EOMSolver {

public:
	static void 				   simulate_world         (World *world, double time_step, std::vector<Collision*> collisions);
	static std::vector<Collision*> get_related_collisions (Object *object, std::vector<Collision*> collisions);
	static void 				   simulate_object        (Object *object, double time_step);
	static void 				   simulate_object        (Object *object, double time_step, std::vector<Collision*> related_collisions);
	static Vector				   compute_impulse        (Object *object, Collision *collision);
	static void 				   apply_angular_impulse  (double& next_d_theta, double impulse, double I);
};

#endif
