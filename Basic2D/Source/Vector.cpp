#include <assert.h>
#include <vector>

#include "Vector.h"

using namespace std;

// - - - - - Constructors - - - - -

Vector::Vector() {
	this->m = 0;
}

Vector::Vector(unsigned int _m) : m(_m) {
	assert(_m >= 0);

	this->entries = new double[this->m];
}

Vector::Vector(double x, double y) : m(2) {
	this->entries = new double[2];
	
	this->entries[0] = x;
	this->entries[1] = y;
}

Vector::Vector(double x, double y, double z) : m(3) {
	this->entries = new double[3];
	
	this->entries[0] = x;
	this->entries[1] = y;
	this->entries[2] = z;
}

// - - - - - Operators - - - - -

double Vector::operator[] (unsigned int index) const {
	assert(index < this->m);
	return this->entries[index];
}

// - - - - - Utility - - - - -

unsigned int Vector::get_dimension() const {
	return this->m;
}
