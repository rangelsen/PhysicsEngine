#include <vector>

#include "object_generation.h"
#include "Object.h"
#include "Vector.h"

using namespace std;

vector<Object*> OBJ_generate_test_objects() {
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

vector<Object*> OBJ_generate_test_objects_simple() {
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

vector<Object*> OBJ_generate_test_objects_multiple() {
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

Object* OBJ_generate_rect(double w, double h) {
	vector<Vector> vertices;
	vertices.push_back(Vector(-w, -h));
	vertices.push_back(Vector(w, -h));
	vertices.push_back(Vector(w, h));
	vertices.push_back(Vector(-w, h));

	Object* rect = new Object(vertices);
	return rect;
}

Object* OBJ_generate_platform(double x, double y) {
	vector<Vector> vertices;
	vertices.push_back(Vector(-5.0, -1.0));	
	vertices.push_back(Vector(5.0, -1.0));	
	vertices.push_back(Vector(5.0, 1.0));	
	vertices.push_back(Vector(-5.0, 1.0));	

	Object* platform = new Object(vertices);
	platform->set_position(Vector(x, y));
	platform->set_movable(false);
	return platform;

}

void OBJ_configure_objects_vertical(vector<Object*> objects) {
    objects.at(0)->set_position(Vector(-1.5, 4.0));
    objects.at(0)->set_velocity(Vector(0, 0));
    objects.at(0)->set_orientation(-.7);

    objects.at(1)->set_movable(false);
    objects.at(1)->set_position(Vector(0, -8));

    if(objects.size() == 3) {
        objects.at(2)->set_position(Vector(1.5, 10.0));
        objects.at(2)->set_velocity(Vector(0.0, 2.0));
        objects.at(2)->set_orientation(-.2);
    }
}

void OBJ_configure_objects_horizontal(vector<Object*> objects) {
    objects.at(0)->set_position(Vector(-3, -3));
    objects.at(0)->set_velocity(Vector(10, 6));
	objects.at(0)->set_orientation(.4);

    objects.at(1)->set_movable(false);
    objects.at(1)->set_position(Vector(8, 0));
    objects.at(1)->set_orientation(3.14/2.0);
}

