#include <GL/glut.h>
#include <vector>
#include <utility>
#include <iostream>

#include "Scene.h"
#include "World.h"
#include "Object.h"
#include "Vector.h"
#include "Collision.h"
#include "Matrix.h"

using namespace std;

void Scene::render_world(World *world) {
    vector<Object*> objects = world->get_objects();

    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned int i = 0; i < objects.size(); i++) {
    	render_object(objects.at(i));
    }

    glFlush();
}

void Scene::render_world(World *world, vector<Collision*> collisions) {
    vector<Object*> objects = world->get_objects();

    float c = .3f;
    glClearColor(c, c, c, c);
    glClear(GL_COLOR_BUFFER_BIT);

    for(unsigned int i = 0; i < objects.size(); i++) {
        render_object(objects.at(i));
    }

    for(unsigned int i = 0; i < collisions.size(); i++) {
        render_contact_point(*collisions.at(i)->get_contact_point());
    }
}

void Scene::render_object(Object *object) {
	vector<Vector> vertices = object->get_vertices();

    // Vertices
	glBegin(GL_POLYGON);
	glColor3f(0.7f, 0.7f, 0.7f);
	for(unsigned int i = 0; i < vertices.size(); i++) {
		double x = vertices.at(i).at(0)/10;
		double y = vertices.at(i).at(1)/10;
		glVertex2d(x, y);
	}
    glEnd();

    // Normals
    /*
    glLineWidth(2.0f); 
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);    
        double x_1 = object->get_position()->at(0);
        double y_1 = object->get_position()->at(1);
        
        for(unsigned int i = 0; i < object->get_normals().size(); i++) {

            double x_2 = x_1 + object->get_normals().at(i).at(0);
            double y_2 = y_1 + object->get_normals().at(i).at(1);

            glVertex2f(x_1/10, y_1/10);
            glVertex2f(x_2/10, y_2/10);
        }
    glEnd();
    */
    // Centroid
	glPointSize(4.0f);
  	glBegin(GL_POINTS);
  		glColor3f(1.0f, 0.0f, 0.0f);
  		double x = object->get_position()->at(0)/10;
  		double y = object->get_position()->at(1)/10;
    	glVertex2f(x, y);
  	glEnd( );
}

void Scene::render_contact_points(vector<Vector> contact_points) {

    glPointSize(4.0f);
    glBegin(GL_POINTS);
        glColor3f(0.0f, 1.0f, 0.0f);
        for(unsigned int i = 0; i < contact_points.size(); i++) {
            double x = contact_points.at(i).at(0)/10;
            double y = contact_points.at(i).at(1)/10;
            glVertex2f(x, y);
        }
    glEnd();
}

void Scene::render_contact_point(Vector contact_point) {

    glPointSize(4.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 0.0f);
        double x = contact_point.at(0)/10.0;
        double y = contact_point.at(1)/10.0;
        glVertex2f(x, y);
    glEnd();
}

void Scene::render_debug(pair<Vector, Vector> ref,
                         pair<Vector, Vector> inc,
                         Vector ref_normal) {

    /* Reference edge */
    glColor3f(1.0, 0.0, 0.0);    
    Scene::draw_line(get<0>(ref), get<1>(ref), 1.0, 0.0, 0.0);

    /* Incident edge */
    glColor3f(0.0, 1.0, 0.0);    
    Scene::draw_line(get<0>(inc), get<1>(inc), 0.0, 1.0, 0.0);
    
    /* Reference normal */
    Vector ref_normal_n = ref_normal.normalize();
    pair<Vector, Vector> ref_norm_p = make_pair(get<0>(ref), get<0>(ref) + ref_normal_n);
    Scene::draw_line(get<0>(ref_norm_p), get<1>(ref_norm_p), 1.0, 0.0, 0.0);                                                
    Scene::draw_point(get<1>(ref_norm_p), 0.0, 0.0, 0.0);
}
                         
void Scene::draw_line(Vector v1, Vector v2, double r, double g, double b) {
   glColor3f(r, g, b);
   glLineWidth(3.0);
   glBegin(GL_LINE_STRIP);
        glVertex2f(v1.at(0)/10.0, v1.at(1)/10.0);
        glVertex2f(v2.at(0)/10.0, v2.at(1)/10.0);
    glEnd();
    glFlush();
}

void Scene::draw_point(Vector p, double r, double b, double g) {
    cout << "Drawing point" << endl;    
    glColor3f(r, g, b);
    glPointSize(4.0);
    glBegin(GL_POINTS);
        glVertex2f(p.at(0)/10.0, p.at(1)/10.0);
    glEnd();
    glFlush();
}
        
