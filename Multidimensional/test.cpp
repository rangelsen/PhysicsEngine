#include <stdio.h>
#include <vector>

#include "Matrix.h"

using namespace std;

int main(int argc, char **argv) {
	
	Matrix *m  = new Matrix(4, 4);
	m->set(2, 2, 1);
	m->set(1, 3, 4.987);

	vector<unsigned int> dim = m->get_dimensions();
	printf("dimensions: [%u, %u]\n", dim.at(0), dim.at(1));

	m->print_console();

	return 0;
}