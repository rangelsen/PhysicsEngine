#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <utility>

class World;
class Object;
class Collision;
class Vector;

class Scene {

public:
	static void render_world(World *world);
	static void render_world(World *world, std::vector<Collision*> collisions);
	static void render_object(Object *object);
	static void render_contact_points(std::vector<Vector> contact_points);
	static void render_contact_point(Vector contact_point);	
        static void render_debug(std::pair<Vector, Vector> ref, std::pair<Vector, Vector> inc, Vector ref_normal);
        static void draw_line(Vector v1, Vector v2, double r, double g, double b);
        static void draw_point(Vector p, double r, double g, double b);
};

#endif
