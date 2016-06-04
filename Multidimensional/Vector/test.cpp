#include <stdio.h>

#include "Vector.h"

using namespace std;

int main(int argc, char** argv) {

	Vector *vec = new Vector(3, 2, 4);
	printf("%f\n", (*vec)[3]);
	return 0;
}