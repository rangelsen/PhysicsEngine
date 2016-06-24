#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

class Matrix {

private:

	// -- Variables ---
	unsigned int m;
	unsigned int n;
	double **entries;
	const std::vector<std::string> initializers = {"zeros", "ones", "identity"};

	// --- Functions ---
	bool is_valid_initializer(std::string initializer);

public:

	// --- Constructors ---
	Matrix();
	Matrix(unsigned int _m, unsigned int _n);
	Matrix(std::string initializer, unsigned int m, unsigned int n);
	Matrix(std::string initializer, unsigned int diagonal);
	~Matrix();

	// --- Operators ---
	Matrix operator= (Matrix *matrix);

	// --- Utility ---
	std::vector<unsigned int> get_dimensions() const;
	void set(unsigned int m, unsigned int n, double entry);
	void print_console() const;
	void print_dimensions() const;
	double & at(unsigned int m, unsigned int n) const;
};

#endif