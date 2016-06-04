#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>

class Object;
class Vector;

typedef enum {
	BLACK   = 30,
	RED     = 31,
	GREEN   = 32,
	YELLOW  = 33,
	BLUE    = 34,
	MAGENTA = 35,
	CYAN    = 36,
	WHITE   = 37
} Color;

struct Display{
	static void object(Object* object, Color color);
	static void error(std::string message);
};

#endif