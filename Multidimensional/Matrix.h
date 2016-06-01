#ifndef MATRIX_H
#define MATRIX_H

class Matrix {

private:

	unsigned int m;
	unsigned int n;
	double **entries;

public:

	// --- Constructors ---
	Matrix();
	Matrix(unsigned int _m, unsigned int _n);

	// --- Operators ---
	// double operator[] (unsigned int m, unsigned n) const;

	// --- Utility ---
	std::vector<unsigned int> get_dimensions() const;
	void set(unsigned int m, unsigned int n, double entry);
	void print_console() const;
};

#endif