#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Vector;
class Matrix;

class Object {

private:

	std::vector<Vector> vertices;
	std::vector<Vector> normals;
	Vector *position;
	Vector *velocity;
	double theta, d_theta;
	double mass;
	double I;
	bool movable;
public:
	
	// --- Constructors ---
	Object();
	Object(std::vector<Vector> vertices);
	~Object();

	// --- Utility ---
	std::vector<Vector> get_vertices() const;
	void 				set_x(float x);
	void 				set_y(float y);
	std::vector<float> 	calculate_centroid() const;
	float 				calculate_signed_area() const;
	void 				update_centroid_position();
	Vector * 			get_position() const;
	Vector *			get_velocity() const;
	void 				set_position(Vector position);
	void 				set_velocity(Vector velocity);
	void				set_orientation(double theta);
	void 				set_rotation(double d_theta);
	double 				get_orientation() const;
	double 				get_rotation() const;
	void 				update_vertices_position(Vector position);
	void 				set_mass(double mass);
	double   			get_mass() const;
	double 				get_moment_of_inertia() const;
	std::vector<Vector> compute_normals(std::vector<Vector> vertices);
	bool 				is_movable() const;
	void 				set_movable(bool movable);
	std::vector<Vector> get_normals() const;
	Matrix *			get_rotation_matrix(double theta) const;
	void 				update_vertices_orientation(double theta);
};

#endif
