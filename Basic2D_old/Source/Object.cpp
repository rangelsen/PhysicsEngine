#include <stdio.h>
#include <vector>

#include "Object.h"
#include "Vector.h"

using namespace std;

// - - - - - Constructors - - - - -

Object::Object() {
	this->x = 0;
	this->y = 0;
}

Object::Object(vector<Vector> vertices) {
	this->vertices = vertices;
	// this->update_centroid_position();
}

/*
// - - - - - Utility - - - - -

vector<Vector> Object::get_vertices() const {
	return this->vertices;
}

void Object::set_x(float position) {
	this->x = position;
}

void Object::set_y(float position) {
	this->y = position;
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

			float cross_factor = current_vertex[0]*next_vertex[1] - next_vertex[0]*current_vertex[0];

			c_x += (current_vertex[0] + next_vertex[0]) * cross_factor;
			c_y += (current_vertex[1] + next_vertex[1]) * cross_factor;
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

			output += (current_vertex[0]*next_vertex[1] - next_vertex[0]*current_vertex[1]);
		}
	}

	output /= 2;

	return output;
}

void Object::update_centroid_position() {
	vector<float> centroid = this->calculate_centroid();
	
	this->set_x(centroid.at(0));
	this->set_y(centroid.at(1));
}
*/