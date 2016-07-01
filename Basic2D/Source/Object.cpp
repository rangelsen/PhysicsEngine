#include <stdio.h>
#include <vector>

#include "Object.h"
#include "Vector.h"
#include "Display.h"

using namespace std;

// - - - - - Constructors - - - - -

Object::Object() {
	this->position = new Vector(0, 0);
	this->velocity = new Vector(0, 0);
	this->theta = 0;
	this->d_theta = 0;
}

Object::Object(vector<Vector> vertices) {
	this->vertices = vertices;

	this->position = new Vector(0, 0);
	this->velocity = new Vector(0, 0);

	this->update_centroid_position();
	this->update_vertices_position();

	this->theta = 0;
	this->d_theta = 0;
	
}

Object::~Object() {
	printf("deleting object\n");
}

// - - - - - Utility - - - - -

vector<Vector> Object::get_vertices() const {
	return this->vertices;
}

vector<float> Object::calculate_centroid() const {
	float a = this->calculate_signed_area();

	float c_x = 0;
	float c_y = 0;

	unsigned int n_vertices = this->vertices.size();

	if(n_vertices > 2) {
		for(int i = 0; i < n_vertices - 1; i++) {
			Vector current_vertex = this->vertices.at(i);
			Vector next_vertex    = this->vertices.at(i+1);

			float cross_factor = current_vertex.at(0)*next_vertex.at(1) - next_vertex.at(0)*current_vertex.at(0);

			c_x += (current_vertex.at(0) + next_vertex.at(0)) * cross_factor;
			c_y += (current_vertex.at(1) + next_vertex.at(1)) * cross_factor;
		}
	}

	vector<float> output;

	if(a != 0) {
		c_x /= 6*a;
		c_y /= 6*a;

		output.push_back(c_x);
		output.push_back(c_y);
	}
	else {
		Display::error("Signed area of object identically equal to zero");
		output.push_back(0);
		output.push_back(0);
	}

	return output;
}


float Object::calculate_signed_area() const {
	float output = 0;
	unsigned int n_vertices = this->vertices.size();

	if(n_vertices > 2) {
		for(int i = 0; i < n_vertices-1; i++) {
			Vector current_vertex = this->vertices.at(i);
			Vector next_vertex    = this->vertices.at(i+1);

			output += (current_vertex.at(0)*next_vertex.at(1)- next_vertex.at(1)*current_vertex.at(1));
		}
	}

	output /= 2;

	return output;
}

void Object::update_centroid_position() {
	vector<float> centroid = this->calculate_centroid();
	
	this->position->at(0) = centroid.at(0);
	this->position->at(1) = centroid.at(1);
}

Vector * Object::get_position() const {
	return this->position;
}
Vector * Object::get_velocity() const {
	return this->velocity;
}

void Object::set_position(Vector position) {
	this->position->at(0) = position.at(0);
	this->position->at(1) = position.at(1);

	this->update_vertices_position();
}

void Object::set_velocity(Vector velocity) {
	this->velocity->at(0) = velocity.at(0);
	this->velocity->at(1) = velocity.at(1);
}

void Object::update_vertices_position() {
	for(unsigned int i = 0; i < this->vertices.size(); i++) {
		this->vertices.at(i) += *this->position;
	}
}