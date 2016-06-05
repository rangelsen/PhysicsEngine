#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "Display.h"
#include "Object.h"
#include "Vector.h"


using namespace std;

void Display::object(Object* object, Color color) {
	printf("\x1b[%d;1m", color);
	printf("Object vertices: \n");

	int n_vertices = object->get_vertices().size();
	
	for(int i = 0; i < n_vertices; i++) {
		Vector vertex = object->get_vertices().at(i);
		unsigned int dimension = vertex.get_dimension();
		
		printf("Vertex: [");

		for(int j = 0; j < dimension; j++) {		
			printf("%f", vertex[j]);
			if(j == dimension - 1)
				printf("]");
			else
				printf(", ");
		}
		printf("\n");
	}
	printf("\x1b[0m");
}

void Display::error(string message) {
	cout << "\x1b[" << RED << ";1m" << "Error: " << message << "." << "\x1b[0m" << endl;
}