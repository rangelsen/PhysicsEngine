#include <stdio.h>
#include <vector>

#include "Matrix.h"

using namespace std;

int main(int argc, char **argv) {
	
	Matrix *m  = new Matrix("zeros", 10, 5);

	vector<unsigned int> dim = m->get_dimensions();
	printf("dimensions: [%u, %u]\n", dim.at(0), dim.at(1));

	m->print_console();

	double entry = (*m)[1][3];
	printf("m[1][3] = %f\n", entry);

	delete m;

	return 0;
}