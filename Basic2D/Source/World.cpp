#include <vector>

#include "World.h"
#include "Object.h"

using namespace std;

World::World() {}

World::World(vector<Object*> _objects) : objects(_objects) {}

int World::get_number_of_objects() {
	return this->objects.size();
}

vector<Object*> World::get_objects() const {
	return this->objects;
}
