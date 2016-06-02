#include <stdio.h>
#include <vector>

#include "Matrix.h"

using namespace std;

int main(int argc, char **argv) {
	
	Matrix *m  = new Matrix("zeros", 10, 5);

	

	delete m;

	return 0;
}