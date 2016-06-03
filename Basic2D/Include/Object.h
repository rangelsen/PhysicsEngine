#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Matrix;

class Object {

private:

	std::vector<Matrix*> vertices;
	float x, y;

public:
	
	// --- Constructors ---
	Object();
	Object(std::vector<Matrix*> vertices);

	// --- Utility ---
	std::vector<Matrix*> get_vertices() const;
	void print_vertices() const;
	void set_x(float x);
	void set_y(float y);
	std::vector<float> calculate_centroid() const;
	float calculate_signed_area() const;
	void update_centroid_position();
};

#endif