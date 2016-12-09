#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>

class Vector;
class Object;
class World;
class Collision;

class CollisionDetector {

private:
	static bool         get_reference_object(Object *a, Object *b, Vector axis_least_penetration); 
	static Vector       get_most_orthogonal_face(Object *object, Vector axis_least_penetration);
	static Vector 	    get_support_point(Object *object, Vector axis);
	static unsigned int get_support_point_index(Object *object, Vector axis);
        static std::vector<Vector> clip(Object* reference, Object* incident, unsigned int vertex_index, Vector axis);

public:
	static Vector 			       collision_detection_SAT(Object *a, Object *b);
	static Vector 			       get_contact_point(Object *a, Object *b, Vector axis_least_penetration);
	static std::vector<Vector>     merge_Vector(std::vector<Vector> vectors_a, std::vector<Vector> vectors_b);
	static std::vector<Collision*> get_collisions(World *world);
	static void 				   compute_apply_positional_correction(Object *object, Collision *collision);
};

#endif
