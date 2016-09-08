#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <string>

class Vector;
class Object;

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
	static void vector(const Vector &v, Color color);
	static void error(std::string message);
	static void object(const Object &object, Color color);
	static void message(std::string, Color color);
};

#endif