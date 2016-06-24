#include <vector>
#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "Matrix.h"
#include "Vector.h"

using namespace std;

// --- Constructors ---
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
	else if(initializer == "identity") {
		assert(_m == _n);
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(i == j)
					this->set(i, j, 1);
				else
					this->set(i, j, 0);
			}
		}
	}
	else {
		cout << "ERROR: Use different constructor for initializer " << initializer << endl;

	}
}

Matrix::Matrix(const Matrix &rhs) : m(rhs.rows()), n(rhs.cols()), entries(NULL) {
	this->entries = new double*[this->m];
	for(int i = 0; i < this->m; i++) {
		this->entries[i] = new double[this->n];
	}
	
	for(int i = 0; i < this->m; i++) {
		for(int j = 0; j < this->n; j++)
			this->set(i, j, rhs.at(i, j));
	}	
}

Matrix::~Matrix() {
	for(int i = 0; i < this->m; i++) {
		if(this->entries[i])
			delete[] this->entries[i];
	}

	if(this->entries)
		delete[] entries;

	this->m = 0;
	this->n = 0;
}

// --- Operators ---
Matrix & Matrix::operator= (const Matrix &rhs) {
	if(!(this->rows() == rhs.rows() && this->cols() == rhs.cols())) {
		if(this->entries)
			delete[] entries;

		this->entries = new double*[rhs.rows()];
		for(int i = 0; i < rhs.cols(); i++)
			this->entries[i] = new double[rhs.cols()];
	}

	this->m = rhs.rows();
	this->n = rhs.cols();

	for(int i = 0; i < this->m; i++) {
		for(int j = 0; j < this->n; j++)
			this->entries[i][j] = rhs.at(i, j);
	}
	return *this;
}

Matrix & Matrix::operator+= (const Matrix &rhs) {
	if ( this->m == rhs.rows() && this->n == rhs.cols() ) {
		for ( unsigned int row = 0; row < this->m; ++row )
			for ( unsigned int column = 0; column < this->n; ++column )
				this->at(row,column) += rhs.at(row,column);
	}

	return *this;
}

Matrix & Matrix::operator-= (const Matrix &rhs) {
	if ( this->m == rhs.rows() && this->n == rhs.cols() ) {
		for ( unsigned int row = 0; row < this->m; ++row )
			for ( unsigned int column = 0; column < this->n; ++column )
				this->at(row,column) -= rhs.at(row,column);
	}

	return *this;
}

Matrix Matrix::operator+ (const Matrix &rhs) const {
	if(this->m == rhs.rows() && this->n == rhs.cols()) {
		return Matrix(*this) += rhs;
	}
	else
		return Matrix();
}

Matrix Matrix::operator- (const Matrix &rhs) const {
	if(this->m == rhs.rows() && this->n == rhs.cols()) {
		return Matrix(*this) -= rhs;
	}
	else
		return Matrix();
}

Matrix Matrix::operator* (const Matrix &rhs) const {
	if(this->n == rhs.rows()) {
		Matrix output(this->m, rhs.cols());

		for(int i = 0; i < this->m; i++) {
			for(int j = 0; j < rhs.cols(); j++) {
				for(int k = 0; k < this->n; k++) {
					output.at(i, j) += this->at(i, k) * rhs.at(k, j);
				}
			}
		}
		return output;
	}
	else
		return Matrix();
}

Matrix Matrix::operator* (double rhs) const {
	Matrix output(*this);

	for(int i = 0; i < this->m; i++) {
		for(int j = 0; j < this->n; j++) {
			double value = this->at(i, j) * rhs;
			output.set(i, j, value);
		}
	}
	return output;
}

Vector Matrix::operator* (const Vector &rhs) const {
	assert(this->n == rhs.get_dimension());

	Vector output(this->m);

	for(int i = 0; i < output.get_dimension(); i++) {
		for(int j = 0; j < this->n; j++) {
			output.at(i) += this->at(i, j) * rhs.at(i);
		}
	}

	return output;
}

//______________________________UTILITY_____________________________

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

double & Matrix::at(unsigned int _m, unsigned int _n) const {
	assert(_m < this->m);
	assert(_n < this->n);

	return entries[_m][_n];
}

unsigned int Matrix::rows() const {
	return this->m;
}

unsigned int Matrix::cols() const {
	return this->n;
}