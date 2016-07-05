#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "Display.h"
#include "Vector.h"
#include "Object.h"


using namespace std;

void Display::vector(const Vector &v, Color color) {
	printf("\x1b[%d;1m", color);

	const unsigned int m = v.get_dimension();
	printf("vector = [");

	for(int i = 0; i < m; i++) {
		printf("%f", v.at(i));
		if(i < m - 1)
			printf(", ");
	}
	printf("]\n");
	printf("\x1b[0m");
}

void Display::error(string message) {
	cout << "\x1b[" << RED << ";1m" << "Error: " << message << "." << "\x1b[0m" << endl;
}

void Display::object(const Object &object, Color color) {
	printf("\x1b[%d;1m", color);
	printf("Object = \n");

	std::vector<Vector> vertices = object.get_vertices();

	for(int i = 0; i < vertices.size(); i++) {
		printf("\t");
		Display::vector(vertices.at(i), color);
	}

	printf("\n");
	printf("\x1b[0m");
}
