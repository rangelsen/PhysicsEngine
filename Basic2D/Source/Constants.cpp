#include <stdio.h>
#include "Constants.h"

Constants *Constants::instance = NULL;

Constants* Constants::Instance() {
	instance = new Constants;
	return instance; 
}