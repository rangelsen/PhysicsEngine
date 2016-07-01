#ifndef SCENE_H
#define SCENE_H

class World;
class Object;

class Scene {

public:
	static void render_world(World *world);
	static void render_object(Object *object);
};
#endif