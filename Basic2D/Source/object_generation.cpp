#include <vector>

#include "object_generation.h"
#include "Object.h"
#include "Vector.h"

using namespace std;

vector<Object*> generate_test_objects() {
	vector<Object*> objects;
	vector<Vector> vertices;

	srand(time(NULL));
	
	vertices.clear();

	// Object 1
	double size = 2;

	vertices.push_back(Vector(-size, -size));
	vertices.push_back(Vector(size, -2*size));
	vertices.push_back(Vector(size, size));
	vertices.push_back(Vector(0, size));

	Object *object_1 = new Object(vertices);

	objects.push_back(object_1);

	vertices.clear();

	// Object 2
	double width = 10;
	double height = 1;

	vertices.push_back(Vector(-width/2.0, -height/2.0));
	vertices.push_back(Vector( width/2.0, -height/2.0));
	vertices.push_back(Vector( width/2.0,  height/2.0));
	vertices.push_back(Vector(-width/2.0,  height/2.0));

	Object *object_2 = new Object(vertices);
	objects.push_back(object_2);

	return objects;
}

vector<Object*> generate_test_objects_simple() {
	vector<Object*> objects;
	vector<Vector> vertices;

	vertices.clear();

	/* Object 1 */
	double size = 2.0;

	vertices.push_back(Vector(-size/2.0, -size));
	vertices.push_back(Vector(size/2.0, -size));
	vertices.push_back(Vector(size/2.0, size));
	vertices.push_back(Vector(-size/2.0, size));

	Object *object_1 = new Object(vertices);

	objects.push_back(object_1);

	vertices.clear();

	/* Object 2 */
	double width = 10;
	double height = 1;

	vertices.push_back(Vector(-width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, height/2.0));
	vertices.push_back(Vector(-width/2.0, height/2.0));

	Object *object_2 = new Object(vertices);
	objects.push_back(object_2);

	return objects;
}

vector<Object*> generate_test_objects_multiple() {
	vector<Object*> objects;
	vector<Vector> vertices;

	vertices.clear();

	/* Object 1 */
	double size = 2;

	vertices.push_back(Vector(-size, -size));
	vertices.push_back(Vector(size, -2*size));
	vertices.push_back(Vector(size, size));
	vertices.push_back(Vector(0, size));

	Object *object_1 = new Object(vertices);
	objects.push_back(object_1);
	vertices.clear();

	/* Object 2 */
	double width = 10;
	double height = 1;

	vertices.push_back(Vector(-width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, height/2.0));
	vertices.push_back(Vector(-width/2.0, height/2.0));

	Object *object_2 = new Object(vertices);
	objects.push_back(object_2);
        vertices.clear();

	/* Object 3 */
	width = 2.0;
	height = 2.0;

	vertices.push_back(Vector(-width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, -height/2.0));
	vertices.push_back(Vector(width/2.0, height/2.0));
	vertices.push_back(Vector(-width/2.0, height/2.0));

	Object* object_3 = new Object(vertices);
	objects.push_back(object_3);
	return objects;
}

Object* generate_rect(double w, double h) {
	vector<Vector> vertices;
	vertices.push_back(Vector(-w, -h));
	vertices.push_back(Vector(w, -h));
	vertices.push_back(Vector(w, h));
	vertices.push_back(Vector(-w, h));

	Object* rect = new Object(vertices);
	return rect;
}
