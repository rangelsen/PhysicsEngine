#include <iostream>
#include <vector>

#include "World.h"

using namespace std;

World::World() {}

void World::add_object(Object *object) {
	this->objects.push_back(object);
}

int World::get_number_of_objects() {
	return this->objects.size();
}
