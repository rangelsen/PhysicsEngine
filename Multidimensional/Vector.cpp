#include <assert.h>
#include "Vector.h"

double & Vector::at(unsigned int _m) {
	return Matrix::at(_m, 0);
}