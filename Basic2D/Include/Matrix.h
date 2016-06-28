#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

#include "Matrix.h"

class Vector;

class Matrix {

protected:
	double **entries;
	unsigned int m;
	unsigned int n;
	
private:

	// -- Variables ---
	const std::vector<std::string> initializers = {"zeros", "ones", "identity"};

	// --- Functions ---
	bool is_valid_initializer(std::string initializer);
	
public:

	// --- Constructors ---
	Matrix();
	Matrix(unsigned int _m, unsigned int _n);
	Matrix(std::string initializer, unsigned int m, unsigned int n);
	Matrix(std::string initializer, unsigned int diagonal);
	Matrix(const Matrix & rhs);
	~Matrix();

	// --- Operators ---
	Matrix & operator=  (const Matrix &rhs);
	Matrix & operator+= (const Matrix &rhs);
	Matrix & operator-= (const Matrix &rhs);
	Matrix   operator+  (const Matrix &rhs) const;
	Matrix   operator-  (const Matrix &rhs) const;
	Matrix   operator*  (const Matrix &rhs) const;
	Matrix   operator*  (double rhs)        const;
	Vector   operator*  (const Vector &rhs) const;

	// --- Utility ---
	void invalidate();
	std::vector<unsigned int> get_dimensions() const;
	void set(unsigned int m, unsigned int n, double entry);
	void print_console() const;
	void print_dimensions() const;
	double & at(unsigned int m, unsigned int n) const;
	unsigned int rows() const;
	unsigned int cols() const;
	Matrix & vertcat(const Matrix &matrix);
};

#endif