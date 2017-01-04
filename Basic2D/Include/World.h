#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Object;
class Collision;

class World {
private:
	std::vector<Object*> objects;

public:
	// --- Constructors ---
	World();
	World(std::vector<Object*> _objects);
	~World();

	// --- Utility ---
	// void add_object(Object object);
	unsigned int 		 get_number_of_objects() const;
	std::vector<Object*> get_objects() const;
	void 			     add_object(Object* object);
};

#endif
