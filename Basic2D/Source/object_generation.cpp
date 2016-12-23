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

    double width = 1;
    double height = 10;

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

vector<Object*> generate_test_objects_simple() {
	vector<Object*> objects;
	vector<Vector> vertices;

	vertices.clear();

	/* Object 1 */
	double size = 2.0;

        vertices.push_back(Vector(-size, -size));
        vertices.push_back(Vector(size, -size));
        vertices.push_back(Vector(size, size));
        vertices.push_back(Vector(-size, size));

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
        height = 1.0;

        vertices.push_back(Vector(-width/2.0, -height/2.0));
        vertices.push_back(Vector(width/2.0, -height/2.0));
        vertices.push_back(Vector(width/2.0, height/2.0));
        vertices.push_back(Vector(-width/2.0, height/2.0));

        Object* object_3 = new Object(vertices);
        objects.push_back(object_3);
	return objects;
}
