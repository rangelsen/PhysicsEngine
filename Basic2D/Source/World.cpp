#include <vector>

#include "World.h"
#include "Object.h"
#include "Collision.h"

using namespace std;

World::World() {}


World::World(vector<Object*> _objects) : objects(_objects) {}

World::~World() {
	for(int i = 0; i < this->objects.size(); i++) {
		delete this->objects.at(i);		
	}
}

unsigned int World::get_number_of_objects() const {
	return this->objects.size();
}

vector<Object*> World::get_objects() const {
	return this->objects;
}
