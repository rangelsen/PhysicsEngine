#ifndef CONSTANTS_H
#define CONSTANTS_H

class Matrix;

class Constants {

private:
	Constants();
	static Constants *instance;
public:
	const float g                 =  5;	
	const float drag_coefficient  = .8;
	const float restitution       = 0.6;
	const float impulse_tolerance = .001;
	const Matrix *A;
	static Constants *Instance();
};

#endif
