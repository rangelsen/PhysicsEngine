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
    TODO: Implement MathLib instead
*/

int window_w = 800;
int window_h = 600;

World *world;

clock_t clocks_0 = 0;
clock_t clocks_1;
unsigned int delta_time_ms = 10;
double delta_time = delta_time_ms/1000.0;
float elapsed_ms;

void clear_collisions(vector<Collision*> collisions) {
	for(size_t i = 0; i < collisions.size(); i++) {
		delete collisions.at(i);	
	}
	
	collisions.clear();
}

void run() {

    clocks_1 = clock();
    elapsed_ms = float(clocks_1 - clocks_0) / (CLOCKS_PER_SEC/1000);

    if(elapsed_ms >= delta_time_ms) {
        clocks_0 = clocks_1;

        /* Find collisions */
        vector<Collision*> collisions = CollisionDetector::get_collisions(world);

        /* Simulate */
		EOMSolver::resolve_collisions(world, collisions, delta_time);

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
			double orientation = rand() % 1 + 1;

			Object* rect = generate_rect(w, h);
			double x_obj =  (x - window_w/2)/10;
			double y_obj = -(y - window_h/2)/10;
			cout << "x = " << x_obj << endl;
			cout << "y = " << y_obj << endl;
			rect->set_position(Vector(x_obj, y_obj));
			rect->set_orientation(orientation);
			world->add_object(rect);
		}	
		break;
		case GLUT_RIGHT_BUTTON:
		{
			cout << "x = " << x << endl;
			cout << "y = " << y << endl;
			cout << "x_t = " << x - window_w/2 << endl;
			cout << "y_t = " << -(y - window_h/2) << endl;
		}
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

void configure_objects_vertical(vector<Object*> objects) {
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

void configure_objects_horizontal(vector<Object*> objects) {
    objects.at(0)->set_position(Vector(-3, -3));
    objects.at(0)->set_velocity(Vector(10, 6));
	objects.at(0)->set_orientation(.4);

    objects.at(1)->set_movable(false);
    objects.at(1)->set_position(Vector(8, 0));
    objects.at(1)->set_orientation(3.14/2.0);
}


int main(int argc, char** argv) {
    
    vector<Object*> objects = generate_test_objects_multiple();
    configure_objects_vertical(objects);
    // configure_objects_horizontal(objects);

    world = new World(objects);

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
