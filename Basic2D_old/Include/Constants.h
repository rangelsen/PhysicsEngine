#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {

private:
	Constants(){};
	static Constants *instance;
public:
	const float g = 9.81;
	const float drag_coefficient = .8;
	const float mass = 1;
	static Constants *Instance();
};

#endif