#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

#include <fstream>

class Object;
class Vector;
class Collision;
class World;

class EOMSolver {

public:
	static void 	           resolve_collisions(World* world, std::vector<Collision*> collisions, double time_step);
	static void 			   apply_impulse(Object* object, Vector impulse, Vector contact_point, double time_step);
	static void 			   step(Object* object, double time_step);
	static void 		       simulate_world         (World *world, double time_step, std::vector<Collision*> collisions);
	static std::vector<Collision*> get_related_collisions (Object *object, std::vector<Collision*> collisions);
	static void 		       simulate_object        (Object *object, double time_step);
	static void 		       simulate_object        (Object *object, double time_step, std::vector<Collision*> related_collisions);
	static Vector		       compute_impulse        (Collision *collision);
	static Vector		       compute_impulse_two    (Collision *collision);
	static void 		       apply_angular_impulse  (double& next_d_theta, double impulse, double I);
};

#endif
