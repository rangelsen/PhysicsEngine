#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "Vector.h"
#include "Display.h"

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
		output.at(i) = this->at(i) * rhs;
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

Vector Vector::operator- (const Vector &rhs) const {
	if(this->get_dimension() == rhs.get_dimension()) {
		Vector output(*this);

		for(int i = 0; i < this->get_dimension(); i++)
			output.at(i) -= rhs.at(i);

		return output;
	}
	else
		return Vector();
}

Vector & Vector::operator+= (const Vector &rhs) {
	if(this->get_dimension() == rhs.get_dimension()) {
		for(unsigned int i = 0; i < this->get_dimension(); i++) {
			this->at(i) += rhs.at(i);
		}
	}
	return *this;
}

Vector & Vector::operator*= (double scalar) {

	for(unsigned int i = 0; i < this->get_dimension(); i++) {
		this->at(i) *= scalar;
	}
	return *this;
}

bool Vector::operator== (const Vector &rhs) const {
	assert(this->get_dimension() == rhs.get_dimension());

	bool output = true;

	for(unsigned int i = 0; i < this->get_dimension(); i++) {
		if(this->at(i) != rhs.at(i)) {
			output = false;
			break;
		}
	}

	return output;
}

unsigned int Vector::get_dimension() const {
	return this->rows();
}

Vector & Vector::vertcat(const Vector &vector) {
	const unsigned int m_expanded = this->m + vector.get_dimension();

	// Reallocate
	double **expanded = new double*[m_expanded];
	for(int i = 0; i < m_expanded; i++)
		expanded[i] = new double[1];

	// Copy entries and add entries from vector
	for(int i = 0; i < m_expanded; i++) {
		if(i < this->m)
			expanded[i][0] = this->entries[i][0];
		else
			expanded[i][0] = vector.at(i - this->m);
	}

	this->m = m_expanded;
	this->entries = expanded;

	return *this;
}

// Takes the 2-norm of the vector
double Vector::norm() const {
	double sum = 0;

	for(unsigned int i = 0; i < this->get_dimension(); i++) {
		sum += pow(this->at(i), 2);
	}

	return sqrt(sum);
}

double Vector::dot(const Vector &rhs) const {
	assert(this->get_dimension() == rhs.get_dimension());

	double output = 0;

	for(unsigned int i = 0; i < this->get_dimension(); i++) {
		output += this->at(i) * rhs.at(i);
	}

	return output;
}

/**
	Calculates the cross product between
	the v = [v1 v2 0] and u = [0 0 u3]
	
	@param u3
	@return Cross product vector
*/
Vector Vector::cross2D(double x) const {
	assert(this->get_dimension() == 2);
	return Vector(-x*this->at(1), x*this->at(0));
}

double Vector::cross2D(const Vector& rhs) const {
	assert(this->get_dimension() == 2);
	return -this->at(1) * rhs.at(0) + this->at(0) * rhs.at(1);
}

Vector Vector::project(const Vector &axis) const {

	return *this * (this->dot(axis) / (this->norm() * axis.norm()));
}

Vector & Vector::normalize() {

	*this *= 1.0/this->norm();
	return *this;
}

void Vector::set(const Vector &rhs) {
	
	assert(this->get_dimension() == rhs.get_dimension());

	for(unsigned int i = 0; i < this->get_dimension(); i++) {

		this->at(i) = rhs.at(i);
	}
}

