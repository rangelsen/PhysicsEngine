#include <stdio.h>
#include <vector>

#include "Matrix.h"
#include "Vector.h"

using namespace std;

int main(int argc, char **argv) {
	
	Vector v("ones", 5);

	printf("%f\n", v.at(5));

	return 0;
}