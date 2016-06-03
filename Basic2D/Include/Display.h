#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>

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
	static void color_print(Color color, Object* objects);
};

#endif