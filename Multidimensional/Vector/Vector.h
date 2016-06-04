#ifndef VECTOR_H
#define VECTOR_H

class Vector {

private:
	unsigned int m;
	double *entries;
public:
	// --- Constructors ---
	Vector();
	Vector(unsigned int m);
	Vector(double x, double y);
	Vector(double x, double y, double z);

	// --- Operators ---
	double operator[] (unsigned int index) const;

	// Utility
};

#endif