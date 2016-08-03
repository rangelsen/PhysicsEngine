#ifndef SCENE_H
#define SCENE_H

#include <vector>

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
};

#endif