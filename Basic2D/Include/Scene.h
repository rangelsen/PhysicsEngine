#ifndef SCENE_H
#define SCENE_H

class World;
class Object;
class Collision;

class Scene {

public:
	static void render_world(World *world, std::vector<Collision*> collisions);
	static void render_object(Object *object);
};
#endif