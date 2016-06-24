#include <stdio.h>
#include <assert.h>
#include "Vector.h"

double & Vector::at(unsigned int _m) const {
	return Matrix::at(_m, 0);
}

Vector::Vector(double x, double y) : Matrix(2, 1) {
	Matrix::at(0, 0) = x;
	Matrix::at(1, 0) = y;
}

Vector Vector::operator* (double rhs) const {
	Vector output(*this);

	for(int i = 0; i < this->get_dimension(); i++) {
		output.at(i) = this->at(i) * 2;
	}
	return output;
}

Vector Vector::operator+ (const Vector &rhs) const {
	if(this->get_dimension() == rhs.get_dimension()) {
		Vector output(*this);

		for(int i = 0; i < this->get_dimension(); i++)
			output.at(i) += rhs.at(i);

		return output;
	}
	else
		return Vector();
}

unsigned int Vector::get_dimension() const {
	return this->rows();
}
