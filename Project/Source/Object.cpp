#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <assert.h>
#include <utility>
#include <cmath>

#include "Object.h"
#include "Vector.h"
#include "Display.h"
#include "Matrix.h"

using namespace std;

/* ---------------- Constructors ---------------- */

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
	this->mass = .05;
	this->I    = .5;
	this->movable = true;
	this->normals = this->compute_normals(this->vertices);
}

Object::~Object() {
	printf("deleting object\n");
	delete this->position;
	delete this->velocity;
}



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

/* ------------------------------- Utility ------------------------------- */

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

    this->update_vertices_orientation(theta - this->theta);
    this->normals = this->compute_normals(this->vertices);
    this->theta = theta;
}

void Object::set_angular_velocity(double d_theta) {
    this->d_theta = d_theta;
}

double Object::get_orientation() const {
    return this->theta;
}

double Object::get_angular_velocity() const {
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

/**
    Gets the start and end vertices of edge
    that is most perpendicular to specified axis 

    @param: Axis to check
    @return: Return pair of start and end vertex
    TODO: Does not return best edge. Suspect it
          returns the most perpenticular edge instead
*/
pair<Vector, Vector> Object::get_best_edge(Vector axis) const {
    int support_point_index = this->get_support_point(axis);
    Vector support_point    = this->vertices.at(support_point_index);

    Vector v1_left  = this->vertices.at(this->get_neighbor_index(support_point_index, -1));
    Vector v2_right = this->vertices.at(this->get_neighbor_index(support_point_index, 1));

    Vector left  = support_point - v1_left;
    Vector right = v2_right - support_point;

    if(abs(axis.dot(left)) < abs(axis.dot(right)))
        return make_pair(v1_left, support_point);
    else
        return make_pair(support_point, v2_right);
}

/**
    Gets the start and end vertices of edge
    given the start index

    @param: start edge index
    @return: Start and end vertex coordinates
*/
pair<Vector, Vector> Object::get_edge(int index) const {
    
    assert(index < this->get_vertices().size());

    Vector v1 = this->vertices.at(index);
    Vector v2 = this->vertices.at(this->get_neighbor_index(index, 1));

    return make_pair(v1, v2);
}

/**
    Returns the index of the
    vertex that is farthest along axis

    @param: Axis to check distance along
    @return: The point with the max distance
*/
int Object::get_support_point(Vector axis) const {
    int index = 0;
    double max_distance = axis.dot(this->vertices.at(0));

    for(size_t i = 1; i < this->vertices.size(); i++) {
        double distance = axis.dot(this->vertices.at(i));

        if(distance > max_distance) {
            max_distance = distance;
            index = i;
        }
    }

    return index;
}

/**
    Gets next/previous vertex index along
    the winding of the object

    @param: index is start index and dir specifies
            number of indices to move along the
            winding. If dir is negative we move backwards
    @return: index + dir scaled to always fit within
             0 - number of vertices in the object
*/
int Object::get_neighbor_index(int index, int dir) const {
    int size = this->vertices.size(); 
    int output = index + dir;

    if(output >= size)
        output -= size;
    else if(output < 0)
        output += size;

    return output;
}



