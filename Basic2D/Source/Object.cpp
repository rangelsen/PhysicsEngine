#include <stdio.h>
#include <vector>

#include "Object.h"
#include "Matrix.h"
#include "Display.h"

using namespace std;

// - - - - - Constructors - - - - -

Object::Object() {
	this->x = 0;
	this->y = 0;
}

Object::Object(vector<Matrix*> vertices) {
	this->x = 0;
	this->y = 0;
	this->vertices = vertices;
}

// - - - - - Utility - - - - -

vector<Matrix*> Object::get_vertices() const {
	return this->vertices;
}

void Object::print_vertices() const {
	printf("Object vertices: \n");
	
	for(int i = 0; i < this->vertices.size(); i++) {
		Matrix *vertex = this->vertices.at(i);
		vector<unsigned int> dimension = vertex->get_dimensions();
		printf("Vertex: [");

		for(int j = 0; j < dimension.size(); j++)
			printf("%f, ", *((*vertex)[j]));

		printf("]\n");
		delete vertex;
	}
}

vector<float> Object::calculate_centroid() const {
	float a = this->calculate_signed_area();

	float c_x = 0;
	float c_y = 0;

	unsigned int n_vertices = this->vertices.size();

	if(n_vertices > 2) {
		for(int i = 0; i < n_vertices - 1; i++) {
			Matrix *current_vertex = this->vertices.at(i);
			Matrix *next_vertex    = this->vertices.at(i+1);

			float cross_factor = (*current_vertex)[0][0]*(*next_vertex)[0][1] - (*next_vertex)[0][0]*(*current_vertex)[0][0];

			c_x += ((*current_vertex)[0][0] + (*next_vertex)[0][0]) * cross_factor;
			c_y += ((*current_vertex)[1][0] + (*next_vertex)[1][0]) * cross_factor;
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
			Matrix *current_vertex = this->vertices.at(i);
			Matrix *next_vertex    = this->vertices.at(i+1);

			output += ((*current_vertex)[0][0]*(*next_vertex)[1][0] - (*next_vertex)[0][0]*(*current_vertex)[1][0]);
		}
	}

	output /= 2;

	return output;
}