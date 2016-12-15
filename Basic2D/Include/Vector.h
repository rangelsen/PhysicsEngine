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
	Vector   operator* (double rhs)        const;
	Vector   operator+ (const Vector &rhs) const;
	Vector   operator- (const Vector &rhs) const;
	Vector & operator+= (const Vector &rhs);
	Vector & operator*= (double scalar);
	bool     operator== (const Vector &rhs) const;

	// - - - - - Utility - - - - -
	double &     at(unsigned int m) const;
	unsigned int get_dimension() const;
	Vector &     vertcat(const Vector &vector);
	double       norm() const;
	double       dot(const Vector &rhs) const;
	double       cross2D(const Vector &rhs) const;
	Vector       project(const Vector &rhs) const;
	Vector &     normalize();
	void 	     set(const Vector &rhs);
};

#endif
