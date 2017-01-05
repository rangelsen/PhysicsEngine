#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include <fstream>

#include "Vector.h"
#include "Constants.h"
#include "Display.h"
#include "Object.h"
#include "World.h"
#include "EOMSolver.h"
#include "Scene.h"
#include "CollisionDetector.h"
#include "object_generation.h"
#include "Collision.h"

using namespace std;

/*
    TODO: Implement MathLib instead of
		  generic math framework
	TODO: Implement tangential friction
	TODO: Remove objects that are too far away
*/

int window_w = 800;
int window_h = 600;

World *world;

clock_t clocks_0 = 0;
unsigned int timestep_ms = 10;
double timestep = timestep_ms/1000.0;

void clear_collisions(vector<Collision*> collisions) {
	for(size_t i = 0; i < collisions.size(); i++) {
		delete collisions.at(i);	
	}
	
	collisions.clear();
}

void run() {

    clock_t clocks_1 = clock();
    double elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

    if(elapsed_ms >= timestep_ms) {
        clocks_0 = clocks_1;

        /* Find collisions */
        vector<Collision*> collisions = CollisionDetector::get_collisions(world);

        /* Simulate */
		EOMSolver::resolve_collisions(world, collisions, timestep);

        /* Render */
        Scene::render_world(world);

		/* Clear from heap */
		clear_collisions(collisions);
    }
}

void mouse(int button, int state, int x, int y) {
  	if(state == GLUT_DOWN)
	switch(button) {
		case GLUT_LEFT_BUTTON:
		{
			srand(time(NULL));
			double w = rand() % 2 + 1; 
			double h = rand() % 2 + 1; 
			double x_obj =  (x - window_w/2)/10;
			double y_obj = -(y - window_h/2)/10;
			double orientation = rand() % 1 + 1;

			Object* rect = OBJ_generate_rect(w, h);
			rect->set_position(Vector(x_obj, y_obj));
			rect->set_orientation(orientation);
			world->add_object(rect);
		}	
		break;
		case GLUT_RIGHT_BUTTON:
		break;
	}
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv) {

/* ================================================================ */
    // vector<Object*> objects = OBJ_generate_test_objects_multiple();
    // OBJ_configure_objects_vertical(objects);
    // OBJ_configure_objects_horizontal(objects);
	// world = new World(objects);

/* ================================================================ */
	Object* platform = OBJ_generate_platform(0.0, -8.0);
	world = new World();
	world->add_object(platform);

/* ================================================================ */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    glutIdleFunc(run);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
    glutMainLoop();

    delete world;

    return 0;
}
