#include <stdio.h>
#include <vector>

#include "Object.h"
#include "Matrix.h"

using namespace std;

// - - - - - Constructors - - - - -

Object::Object() {}

Object::Object(vector<Matrix*> vertices) {

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