#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Vector;

class Object {

private:

	std::vector<Vector> vertices;
	Vector *position;
	Vector *velocity;
	double theta, d_theta;

public:
	
	// --- Constructors ---
	Object();
	Object(std::vector<Vector> vertices);
	~Object();

	// --- Utility ---
	std::vector<Vector> get_vertices() const;
	void set_x(float x);
	void set_y(float y);
	std::vector<float> calculate_centroid() const;
	float calculate_signed_area() const;
	void update_centroid_position();
	Vector * get_position() const;
	Vector * get_velocity() const;
	void set_position(Vector position);
	void set_velocity(Vector velocity);
};

#endif
