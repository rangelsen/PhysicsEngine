#include <stdio.h>

#include "Constants.h"
#include "Matrix.h"

Constants *Constants::instance = NULL;

Constants::Constants() {
	Matrix *matrix = new Matrix("zeros", 6, 6);
	
	matrix->set(0, 3, 1);
	matrix->set(1, 4, 1);
	matrix->set(2, 5, 1);
	matrix->set(3, 3, -drag_coefficient/mass);
	matrix->set(4, 4, -drag_coefficient/mass);

	this->A = new Matrix(*matrix);
	delete matrix;
}

Constants* Constants::Instance() {
	instance = new Constants;
	return instance; 
}

/*
_________
dx      | 0    0    0     1     0     0 | x 
dy      | 0    0    0     0     1     0 | y
dtheta  | 0    0    0     0     0     1 | theta
ddx     | 0    0    0  -f/m     0     0 | dx
ddy     | 0    0    0     0  -f/m     0 | dy
ddtheta | 0    0    0     0     0     0 | dtheta
_________

*/