#ifndef EOM_SOLVER_H
#define EOM_SOLVER_H

#include <fstream>

class Object;
class Vector;
class Collision;
class World;

class EOMSolver {

public:
	static void   resolve_collisions  (World* world, std::vector<Collision*> collisions, double time_step);
	static void   apply_impulse		  (Object* object, Vector impulse, Vector contact_point, double time_step);
	static void   step				  (Object* object, double time_step);
	static Vector compute_impulse     (Collision *collision);
	static Vector compute_impulse_two (Collision *collision);
};

#endif
