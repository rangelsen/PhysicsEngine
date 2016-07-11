#include <vector>

#include "object_generation.h"
#include "Object.h"
#include "Vector.h"

using namespace std;

vector<Object*> generate_objects() {
	vector<Object*> objects;
	vector<Vector> vertices;

	srand(time(NULL));
	
	vertices.clear();

	double size = 2;

	Vector v5(-size, -size);
	Vector v6(size, 0);
	Vector v7(0, size);

	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);

	Object *object_1 = new Object(vertices);

	objects.push_back(object_1);

	vertices.clear();

	double width = 10;
	double height = 1;

	Vector v1(-width/2.0, height/2.0);
	Vector v2(width/2.0, height/2.0);
	Vector v3(-width/2.0, -height/2.0);
	Vector v4(width/2.0, -height/2.0);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v4);
	vertices.push_back(v3);

	Object *object = new Object(vertices);
	object->set_movable(false);
	object->set_position(Vector(0, -8));
	objects.push_back(object);

	return objects;
}

vector<Object*> generate_convex_polygons(unsigned int n_polygons, unsigned int n_vertices) {

	vector<Object*> objects;
	vector<Vector> vertices;

	srand(time(NULL));
	
	for(int i = 0; i < n_polygons; i++) {
		vertices.clear();
		for(int j = 0; j < n_vertices; j++) {

			double x = rand() % 6 + 2;
			double y = rand() % 6 + 2;

			Vector vertex(x, y);

			vertices.push_back(vertex);
		}

		Object *object = new Object(vertices);
		objects.push_back(object);
	}

	vertices.clear();

	double width = 10;
	double height = 1;

	Vector v1(-width/2.0, height/2.0);
	Vector v2(width/2.0, height/2.0);
	Vector v3(-width/2.0, -height/2.0);
	Vector v4(width/2.0, -height/2.0);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v4);
	vertices.push_back(v3);

	Object *object = new Object(vertices);
	object->set_movable(false);
	object->set_position(Vector(0, -8));
	objects.push_back(object);

	return objects;
}