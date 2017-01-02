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
    TODO: Implement MathLib instead (might be heck of a job)
*/

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

        // EOMSolver::simulate_world(world, delta_time, collisions);

        /* Render */
        Scene::render_world(world, collisions);

        collisions.clear();
    }
}

void configure_objects_vertical(vector<Object*> objects) {
    objects.at(0)->set_position(Vector(-1.0, 4.0));
    objects.at(0)->set_velocity(Vector(0, 0));
    objects.at(0)->set_orientation(-.6);

    objects.at(1)->set_movable(false);
    objects.at(1)->set_position(Vector(0, -8));

    if(objects.size() == 3) {
        objects.at(2)->set_position(Vector(2.5, 10.0));
        objects.at(2)->set_velocity(Vector(0, 10.0));
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
    
    vector<Object*> objects = generate_test_objects();
    configure_objects_horizontal(objects);
    // configure_objects_horizontal(objects);

    world = new World(objects);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Physics Engine");
    glutDisplayFunc(run);
    glutIdleFunc(run);
    glutMainLoop();

    delete world;

    return 0;
}
