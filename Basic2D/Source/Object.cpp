#include <stdio.h>
#include <vector>
#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Display.h"
#include "Matrix.h"

using namespace std;

// - - - - - Constructors - - - - -

Object::Object() {
	this->position = new Vector(0, 0);
	this->velocity = new Vector(0, 0);
	this->theta = 0;
	this->d_theta = 0;
	this->mass = 0;
	this->movable = true;
}

Object::Object(vector<Vector> vertices) {
	this->vertices = vertices;

	this->position = new Vector(0, 0);
	this->velocity = new Vector(0, 0);

	this->update_centroid_position();
	this->set_position(Vector(0, 0));

	this->theta = 0;
	this->d_theta = 0;
	this->mass = 1;
	this->I    = 1;
	this->movable = true;
	this->normals = this->compute_normals(this->vertices);
}

Object::~Object() {
	printf("deleting object\n");
	delete this->position;
	delete this->velocity;
}

// - - - - - Utility - - - - -

vector<Vector> Object::get_vertices() const {
	return this->vertices;
}

vector<float> Object::calculate_centroid() const {
	float a = this->calculate_signed_area();

	float c_x = 0;
	float c_y = 0;

	unsigned int n_vertices = this->vertices.size();

	float cross_factor;

	if(n_vertices > 2) {
		for(int i = 0; i < n_vertices - 1; i++) {
			Vector current_vertex = this->vertices.at(i);
			Vector next_vertex    = this->vertices.at(i+1);

			cross_factor = current_vertex.at(0)*next_vertex.at(1) - next_vertex.at(0)*current_vertex.at(1);

			c_x += (current_vertex.at(0) + next_vertex.at(0)) * cross_factor;
			c_y += (current_vertex.at(1) + next_vertex.at(1)) * cross_factor;
		}
	}

	Vector current_vertex = this->vertices.at(n_vertices - 1);
	Vector next_vertex    = this->vertices.at(0);

	cross_factor = current_vertex.at(0)*next_vertex.at(1) - next_vertex.at(0)*current_vertex.at(1);

	c_x += (current_vertex.at(0) + next_vertex.at(0)) * cross_factor;
	c_y += (current_vertex.at(1) + next_vertex.at(1)) * cross_factor;

	vector<float> output;

	if(a != 0) {
		c_x /= 6*a;
		c_y /= 6*a;

		output.push_back(c_x);
		output.push_back(c_y);
	}
	else {
		Display::error("Signed area of object identically equal to zero");
		output.push_back(0);
		output.push_back(0);
	}

	return output;
}


float Object::calculate_signed_area() const {
	float output = 0;
	unsigned int n_vertices = this->vertices.size();

	if(n_vertices > 2) {
		for(int i = 0; i < n_vertices-1; i++) {
			Vector current_vertex = this->vertices.at(i);
			Vector next_vertex    = this->vertices.at(i+1);

			output += (current_vertex.at(0)*next_vertex.at(1)- next_vertex.at(0)*current_vertex.at(1));
		}
	}

	Vector current_vertex = this->vertices.at(n_vertices - 1);
	Vector next_vertex = this->vertices.at(0);

	output += current_vertex.at(0)*next_vertex.at(1) - next_vertex.at(0)*current_vertex.at(1);
	output /= 2;

	return output;
}

void Object::update_centroid_position() {
	vector<float> centroid = this->calculate_centroid();
	
	this->position->at(0) = centroid.at(0);
	this->position->at(1) = centroid.at(1);
}

Vector * Object::get_position() const {
	return this->position;
}
Vector * Object::get_velocity() const {
	return this->velocity;
}

void Object::set_position(Vector position) {
	this->update_vertices_position(position);
	this->compute_normals(this->vertices);

	this->position->at(0) = position.at(0);
	this->position->at(1) = position.at(1);
}

void Object::set_velocity(Vector velocity) {
	this->velocity->at(0) = velocity.at(0);
	this->velocity->at(1) = velocity.at(1);
}

void Object::set_orientation(double theta) {
	this->update_vertices_orientation(theta);
	this->compute_normals(this->vertices);
	this->theta = theta;
}

void Object::set_rotation(double d_theta) {
	this->d_theta = d_theta;
}

double Object::get_orientation() const {
	return this->theta;
}

double Object::get_rotation() const {
	return this->d_theta;
}

void Object::update_vertices_position(Vector position) {
	Vector diff = position - *this->position;

	for(unsigned int i = 0; i < this->vertices.size(); i++) {
		this->vertices.at(i) += diff;
	}
}

void Object::set_mass(double mass) {
	this->mass = mass;
}

double Object::get_mass() const {
	return this->mass;
}

double Object::get_moment_of_inertia() const {
	return this->I;
}

vector<Vector> Object::compute_normals(vector<Vector> vertices) {
	vector<Vector> normals;

	unsigned int n_vertices = vertices.size();

	Vector current_vertex(2);
	Vector next_vertex(2);
	Vector face(2);
	Vector normal(2);

	for(unsigned int i = 0; i < n_vertices - 1; i++) {
		current_vertex = vertices.at(i);
		next_vertex = vertices.at(i + 1);

		face = next_vertex - current_vertex;
		normal = Vector(face.at(1), -face.at(0));
		normal.normalize();

		normals.push_back(normal);

	}

	current_vertex = vertices.at(vertices.size()-1);
	next_vertex	   = vertices.at(0);
	
	face = next_vertex - current_vertex;
	normal = Vector(face.at(1), -face.at(0));
	normal.normalize();

	normals.push_back(normal);

	return normals;
}

bool Object::is_movable() const {
	return this->movable;
}

void Object::set_movable(bool movable) {
	this->movable = movable;
}

vector<Vector> Object::get_normals() const {
	return this->normals;
}

Matrix * Object::get_rotation_matrix(double theta) const {
	Matrix *rotation = new Matrix(2, 2);

	rotation->at(0, 0) = cos(theta);
	rotation->at(0, 1) = -sin(theta);
	rotation->at(1, 0) = sin(theta);
	rotation->at(1, 1) = cos(theta);

	return rotation;
}

void Object::update_vertices_orientation(double theta) {

	Matrix *rotation_matrix = this->get_rotation_matrix(theta);

	for(unsigned int i = 0; i < this->vertices.size(); i++) {

		Vector centered_vertex = this->vertices.at(i) - *this->get_position();

		Vector rotated_vertex = *rotation_matrix * centered_vertex;

		Vector translated_back = *this->get_position() + rotated_vertex;

		this->vertices.at(i) = translated_back;
	}

	delete rotation_matrix;
}