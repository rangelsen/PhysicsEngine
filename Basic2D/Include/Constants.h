#ifndef CONSTANTS_H
#define CONSTANTS_H

class Matrix;

class Constants {

private:
	Constants();
	static Constants *instance;
public:
	const float g = 20;
	const float drag_coefficient = .8;
	const float mass = 1;
	const Matrix *A;
	static Constants *Instance();
};

#endif