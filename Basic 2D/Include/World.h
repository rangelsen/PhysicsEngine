#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Object;

class World {
private:
	std::vector<Object*> objects;
public:
	World();
	void add_object(Object *object);
	int get_number_of_objects();
};

#endif