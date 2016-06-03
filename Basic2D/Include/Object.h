#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Matrix;

class Object {

private:

	std::vector<Matrix*> vertices;
public:
	
	// --- Constructors ---
	Object();
	Object(std::vector<Matrix*> vertices);

	// --- Utility ---
	std::vector<Matrix*> get_vertices() const;
	void print_vertices() const;
};

#endif