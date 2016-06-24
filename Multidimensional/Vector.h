#ifndef VECTOR_H
#define VECTOR_H

#include <string>

#include "Matrix.h"

class Vector : public Matrix {

public:
	Vector() : Matrix() {}
	Vector(unsigned int m) : Matrix(m, 1) {}
	Vector(std::string initializer, unsigned int m) : Matrix(initializer, m, 1) {}

	// - - - - - Utility - - - - -
	double & at(unsigned int m);
};

#endif