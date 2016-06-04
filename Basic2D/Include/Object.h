#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Vector;

class Object {

private:

	std::vector<Vector*> vertices;
	float x, y;

public:
	
	// --- Constructors ---
	Object();
	Object(std::vector<Vector*> vertices);

	// --- Utility ---
	std::vector<Vector*> get_vertices() const;
	void print_vertices() const;
	void set_x(float x);
	void set_y(float y);
	std::vector<float> calculate_centroid() const;
	float calculate_signed_area() const;
	void update_centroid_position();
};

#endif