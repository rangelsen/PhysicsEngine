#include <vector>
#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "Matrix.h"

using namespace std;

//  - - - - - Constructors - - - - -
Matrix::Matrix() {

	this->m = 0;
	this->n = 0;
}

Matrix::Matrix(unsigned int _m, unsigned int _n) : m(_m), n(_n) {

	assert(_m >= 0);
	assert(_n >= 0);

	const unsigned int rows = this->m;
	const unsigned int cols = this->n;

	this->entries = new double*[rows];
	for(int i = 0; i < rows; i++) {
		this->entries[i] = new double[cols];
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			this->set(i, j, 0);
		}
	}
}

Matrix::Matrix(string initializer, unsigned int _m, unsigned int _n) : m(_m), n(_n) {

	assert(_m >= 0);
	assert(_n >= 0);
	assert(this->is_valid_initializer(initializer));

	const unsigned int rows = this->m;
	const unsigned int cols = this->n;

	this->entries = new double*[rows];

	for(int k = 0; k < rows; k++) {
		this->entries[k] = new double[cols];
	}

	if(initializer == "zeros") {

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				this->set(i, j, 0);
			}
		}
	}
	else if(initializer == "ones") {

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				this->set(i, j, 1);
			}
		}
	}
	else {
		cout << "ERROR: Use different constructor for initializer " << initializer << endl;

	}
}

Matrix::Matrix(Matrix *matrix) {

	vector<unsigned int> dimension = matrix->get_dimensions();
	
	this->m = dimension.at(0);
	this->n = dimension.at(1);

	this->entries = new double*[this->m];
	
	for(int h = 0; h < this->m; h++)
		this->entries[h] = new double[this->n];

	
	for(int i = 0; i < this->m; i++) {
		for(int j = 0; j < this->n; j++) {

			this->entries[i][j] = (*matrix)[i][j];
		}
	}
}

// - - - - - Destructors - - - - -

Matrix::~Matrix() {

	for(int i = 0; i < this->m; i++) {
		delete[] this->entries[i];
	}
}

// - - - - - Operators - - - - -

double * Matrix::operator[] (unsigned int m) const {
	
	return this->entries[m];
}

/*
void Matrix::operator= (Matrix *matrix) {

	Matrix *output = new Matrix(matrix);
}
*/

// - - - - - Utility - - - - -

vector<unsigned int> Matrix::get_dimensions() const {

	vector<unsigned int> dimension(2, 0);
	
	dimension[0] = this->m;
	dimension[1] = this->n;

	return dimension;
}

void Matrix::set(unsigned int m, unsigned int n, double entry) {

	if ((m < this->m) && (n < this->n))
		this->entries[m][n] = entry;
	else
		printf("\x1b[31;1m Error: Dimensions out of bounds \x1b[0m \n");
}

void Matrix::print_console() const {

	printf("Matrix = \n");

	for(int i = 0; i < this->m; i++) {
		for(int j = 0; j < this->n; j++) {

			printf("%f\t", this->entries[i][j]);
		}
		printf("\n");
	}
}

bool Matrix::is_valid_initializer(string initializer) {

	bool output = false;

	for(int i = 0; i < this->initializers.size(); i++) {
		if(initializer == this->initializers.at(i)) {
			output = true;
			break;
		}
	}

	return output;
}

void Matrix::print_dimensions() const {
	printf("Matrix dimension: [%u, %u]\n", this->m, this->n);
}