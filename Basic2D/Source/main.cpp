#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include <fstream>

#include "Matrix.h"
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
        Scene::render_world(world); //, collisions);

        collisions.clear();
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
			rect->set_position(Vector((x - window_w)/200.0, (-y - window_h)/200.0));
			rect->set_orientation(orientation);
			world->add_object(rect);
		}	
		break;
		case GLUT_RIGHT_BUTTON:
		{
			cout << world->get_objects().size() << endl;
			for(size_t i = 0; i < world->get_objects().size(); i++) {
				Display::vector(*world->get_objects().at(i)->get_position(), MAGENTA);
			}
		}
		break;
	}
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
	glutMouseFunc(mouse);
    glutIdleFunc(run);
    glutMainLoop();

    delete world;

    return 0;
}
