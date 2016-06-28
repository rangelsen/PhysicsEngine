#include <stdio.h>

#include "Constants.h"
#include "Matrix.h"

Constants *Constants::instance = NULL;

Constants::Constants() {
	Matrix *matrix = new Matrix("zeros", 6, 6);
	
	matrix->set(0, 3, 1);
	matrix->set(1, 4, 1);
	matrix->set(2, 5, 1);
	matrix->set(3, 3, drag_coefficient/mass);
	matrix->set(4, 4, drag_coefficient/mass);

	this->A = new Matrix(*matrix);
	delete matrix;
}

Constants* Constants::Instance() {
	instance = new Constants;
	return instance; 
}