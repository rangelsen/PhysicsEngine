#include <assert.h>
#include "Vector.h"

double & Vector::at(unsigned int _m) {
	return Matrix::at(_m, 0);
}

Vector::Vector(double x, double y) : Matrix(2, 1) {
	Matrix::at(0, 0) = x;
	Matrix::at(1, 0) = y;
}