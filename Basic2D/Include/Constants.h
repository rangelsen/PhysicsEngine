#ifndef CONSTANTS_H
#define CONSTANTS_H

class Matrix;

class Constants {

private:
	Constants();
	static Constants *instance;
public:
	const float g                 =  5;	
	const float restitution       = 0.3;
	const float impulse_tolerance = .001;
	static Constants *Instance();
};

#endif
