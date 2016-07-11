#include <vector>
#include <iostream>

#include "CollisionTest.h"
#include "Object.h"
#include "Vector.h"
#include "Display.h"

using namespace std;

bool CollisionTest::collision_detection_SAT(Object *a, Object *b) {

	vector<Vector> vertices_a = a->get_vertices();
	vector<Vector> vertices_b = b->get_vertices();
	vector<Vector> normals_a  = a->get_normals();
	vector<Vector> normals_b  = b->get_normals();

	vector<Vector> normals = CollisionTest::merge_Vector(normals_a, normals_b);

// ____________________________________________________________
/*
	cout << "Object a: " << endl;
	Display::object(*a, YELLOW);
	Display::object(*b, YELLOW);

	cout << "Normals a: " << endl;
	for(unsigned int i = 0; i < normals_a.size(); i++) {
		Display::vector(normals_a.at(i), MAGENTA);
	}

	cout << "Normals b: " << endl;
	for(unsigned int i = 0; i < normals_b.size(); i++) {
		Display::vector(normals_b.at(i), MAGENTA);
	}

	cout << "Normals merged: " << endl;
	for(unsigned int i = 0; i < normals.size(); i++) {
		Display::vector(normals.at(i), MAGENTA);
	}

	cout << "START" << endl;
*/
// ____________________________________________________________

	Vector current_normal = normals_a.at(0);

	double min_a, max_a;
	double min_b, max_b;

// ____________________________________________________________

	vector<bool> overlaps;

	for(unsigned int i = 0; i < normals.size(); i++) {

		current_normal = normals.at(i);
	/*
		cout << "Current normal: " << endl;
		Display::vector(current_normal, BLUE);
	*/
		min_a = vertices_a.at(0).dot(current_normal);
		max_a = min_a;
		min_b = vertices_b.at(0).dot(current_normal);
		max_b = min_b;
	/*
		cout << "Vertices of a" << endl;
		cout << "Current vertex : " << endl;
		Display::vector(vertices_a.at(0), WHITE);
		
		cout << "Scalar projection: " << min_a << endl;
	*/
		for(unsigned int j = 1; j < vertices_a.size(); j++) {

		/*
			cout << "Current vertex : " << endl;
			Display::vector(vertices_a.at(j), WHITE);
		*/
			double scalar_projection = vertices_a.at(j).dot(current_normal);
			
			// cout << "Scalar projection: " << scalar_projection << endl;

			if(scalar_projection < min_a) {
				min_a = scalar_projection;
			}
			
			if(scalar_projection > max_a) {
				max_a = scalar_projection;
			}
		}
	/*
		cout << "Vertices of b" << endl;
		cout << "Current vertex : " << endl;
		cout << "Scalar projection: " << min_b << endl;
		Display::vector(vertices_b.at(0), WHITE);
	*/
		for(unsigned int j = 1; j < vertices_b.size(); j++) {
			// cout << "Current vertex : " << endl;
			// Display::vector(vertices_b.at(j), WHITE);

			double scalar_projection = vertices_b.at(j).dot(current_normal);

			// cout << "Scalar projection: " << scalar_projection << endl;

			if(scalar_projection < min_b) {
				min_b = scalar_projection;
			}
			if(scalar_projection > max_b) {
				max_b = scalar_projection;
			}
		}
	/*
		cout << "min_a = " << min_a << endl;
		cout << "max_a = " << max_a << endl;
		cout << "min_b = " << min_b << endl;
		cout << "max_b = " << max_b << endl;
	*/
		if((min_b - max_a) > 0) {
			overlaps.push_back(true);
			// printf("#\n");
		}
		else if((min_a - max_b) > 0) {
			overlaps.push_back(true);
			// printf("##\n");
		}
		else
			overlaps.push_back(false);
	}

	bool collision = false;
	unsigned int n_overlaps = 0;

	// cout << "Overlaps:";
	for(unsigned int i = 0; i < overlaps.size(); i++) {
		// cout << " " << overlaps.at(i);

		if(!overlaps.at(i))
			n_overlaps++;
	}
	// cout << endl;

	if(n_overlaps == normals.size())
		return true;
	else
		return false;

}

vector<Vector> CollisionTest::merge_Vector(vector<Vector> vectors_a, vector<Vector> vectors_b) {

    vector<Vector> output;
    output = vectors_a;

    for(unsigned int i = 0; i < vectors_b.size(); i++) {

    	output.push_back(vectors_b.at(i));
    }

    return output;
}