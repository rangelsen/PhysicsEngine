#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {

private:
	Constants(){};
	static Constants *instance;
public:
	const float g = 9.81;
	static Constants *Instance();
};

#endif