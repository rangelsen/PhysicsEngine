#include <GL/glut.h>
#include <vector>

#include "Scene.h"
#include "World.h"
#include "Object.h"
#include "Vector.h"

using namespace std;

void Scene::render_world(World *world) {
	vector<Object*> objects = world->get_objects();

    glClear(GL_COLOR_BUFFER_BIT);
    for(unsigned int i = 0; i < objects.size(); i++) {
    	render_object(objects.at(i));
    }
    glFlush();
}

void Scene::render_object(Object *object) {
	vector<Vector> vertices = object->get_vertices();

	glBegin(GL_POLYGON);
	for(unsigned int i = 0; i < vertices.size(); i++) {
		double x = vertices.at(i).at(0)/100;
		double y = vertices.at(i).at(1)/100;
		glVertex2d(x, y);
	}
    glEnd();
}