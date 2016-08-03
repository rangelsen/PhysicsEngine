#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

class Object;
class Vector;
class Collision;
class World;

class EOMSolver {

public:
	static void 				  simulate_world(World *world, double time_step, std::vector<Collision*> collisions);
	static std::vector<Collision*> get_related_collisions(Object *object, std::vector<Collision*> collisions);
	static void 				  simulate_object(Object *object, double time_step);
	static void 				  simulate_object(Object *object, double time_step, std::vector<Collision*> related_collisions);
	static Vector 			  	  evaluate_forces(Object *object, std::vector<Collision*> related_collisions, double delta_time);
	static double 				  evaluate_torque(Object *object, std::vector<Collision*> related_collisions);
};

#endif