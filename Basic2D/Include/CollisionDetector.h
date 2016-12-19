#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <vector>

class Vector;
class Object;
class World;
class Collision;

class CollisionDetector {

private:
	static bool                 flip_objects(Object *a, Object *b, Vector axis_normalized);
	static Vector               get_most_orthogonal_face(Object *object, Vector axis_least_penetration);
	static Vector 	            get_support_point(Object *object, Vector axis);
	static unsigned int         get_support_point_index(Object *object, Vector axis);
        static std::vector<Vector>  clip(Vector v1, Vector v2, Vector n, double offset);

public:
	static std::pair<bool, Vector> collision_detection_SAT(Object *a, Object *b);
	static std::vector<Vector>     get_contact_points(Object *a, Object *b, Vector axis_least_penetration);
	static std::vector<Vector>     merge_Vector(std::vector<Vector> vectors_a, std::vector<Vector> vectors_b);
	static std::vector<Collision*> get_collisions(World *world);
	static void 	               compute_apply_positional_correction(Collision *collision);
};

#endif
