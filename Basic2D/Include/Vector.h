#ifndef VECTOR_H
#define VECTOR_H

#include <string>

#include "Matrix.h"

class Vector : public Matrix {

public:
	// - - - - - Constructors - - - - -
	Vector() : Matrix() {}
	Vector(unsigned int m) : Matrix(m, 1) {}
	Vector(std::string initializer, unsigned int m) : Matrix(initializer, m, 1) {}
	Vector(double x, double y);

	// - - - - - Operators - - - - -
	Vector operator* (double rhs)        const;
	Vector operator+ (const Vector &rhs) const;
	Vector & operator+= (const Vector &rhs);

	// - - - - - Utility - - - - -
	double & at(unsigned int m) const;
	unsigned int get_dimension() const;
	Vector & vertcat(const Vector &vector);
};

#endif