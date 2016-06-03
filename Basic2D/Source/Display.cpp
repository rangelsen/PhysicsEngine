#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "Display.h"
#include "Object.h"
#include "Matrix.h"

using namespace std;

void Display::object(Object* object, Color color) {
	printf("\x1b[%d;1m", color);
	printf("Object vertices: \n");

	int n_vertices = object->get_vertices().size();
	Matrix *vertex;
	
	for(int i = 0; i < n_vertices; i++) {
		vertex = object->get_vertices().at(i);
		vector<unsigned int> dimension = vertex->get_dimensions();
		printf("Vertex: [");

		for(int j = 0; j < dimension.size(); j++) {		
			printf("%f", *((*vertex)[j]));
			if(j == dimension.size() - 1)
				printf("]");
			else
				printf(", ");
		}
		printf("\n");
	}
	delete vertex;
	printf("\x1b[0m");
}

void Display::error(string message) {
	cout << "\x1b[" << RED << ";1m" << "Error: " << message << "." << "\x1b[0m" << endl;
}