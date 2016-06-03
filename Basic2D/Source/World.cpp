#include <vector>

#include "World.h"
#include "Object.h"

using namespace std;

World::World() {}

World::World(vector<Object*> _objects) : objects(_objects) {}

void World::add_object(Object *object) {
	this->objects.push_back(object);
}

int World::get_number_of_objects() {
	return this->objects.size();
}
