#include <stdio.h>

#include "Constants.h"
#include "Matrix.h"

Constants *Constants::instance = NULL;

Constants::Constants() {}

Constants* Constants::Instance() {
	instance = new Constants;
	return instance; 
}