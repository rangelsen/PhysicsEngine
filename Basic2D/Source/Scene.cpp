#include <GL/glut.h>
#include <vector>

#include "Scene.h"
#include "World.h"
#include "Object.h"
#include "Vector.h"
#include "Collision.h"

using namespace std;

void Scene::render_world(World *world, vector<Collision*> collisions) {
	vector<Object*> objects = world->get_objects();

    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned int i = 0; i < objects.size(); i++) {
    	render_object(objects.at(i));
    }

    for(unsigned int i = 0; i < collisions.size(); i++) {
        for(unsigned int j = 0; j < collisions.at(i)->get_contact_points().size(); j++) {
            
            Vector contact_point = collisions.at(i)->get_contact_points().at(j);

            glPointSize(4.0f);
            glBegin(GL_POINTS);
                glColor3f(0.0f, 1.0f, 0.0f);
                double x = contact_point.at(0)/10;
                double y = contact_point.at(1)/10;
                glVertex2f(x, y);
            glEnd();
        }
    }

    glFlush();
}

void Scene::render_object(Object *object) {
	vector<Vector> vertices = object->get_vertices();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	for(unsigned int i = 0; i < vertices.size(); i++) {
		double x = vertices.at(i).at(0)/10;
		double y = vertices.at(i).at(1)/10;
		glVertex2d(x, y);
	}
    glEnd();

	glPointSize( 4.0f );
  	glBegin(GL_POINTS);
  		glColor3f( 1.0f, 0.0f, 0.0f );
  		double x = object->get_position()->at(0)/10;
  		double y = object->get_position()->at(1)/10;
    	glVertex2f(x, y);
  	glEnd( );
}