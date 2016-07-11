#include <vector>
#include <iostream>

#include "CollisionTest.h"
#include "Object.h"
#include "Vector.h"

using namespace std;

Vector CollisionTest::collision_detection_SAT(Object *a, Object *b) {

	vector<Vector> vertices_a = a->get_vertices();
	vector<Vector> vertices_b = b->get_vertices();

	Vector position_offset = *a->get_position() - *b->get_position();

	vector<Vector> normals_a = a->get_normals();
/*
	cout << "vertices_a.size = " << vertices_a.size() << endl;
	cout << "normals_a.size = " << normals_a.size() << endl;
*/
	double min_a, min_b;
	double max_a, max_b;
	double test, test_1, test_2;
	double offset;
	bool flag = false;

	Vector normal(2);

	for(unsigned int i = 0; i < vertices_a.size(); i++) {

		normal = normals_a.at(i);

		min_a = normal.dot(vertices_a.at(0));
		max_a = min_a;

		for(unsigned int j = 1; j < vertices_a.size(); j++) {

			test = normal.dot(vertices_a.at(j));

			if(test < min_a)
				min_a = test;
			if(test > max_a)
				max_a = test;
		}

		min_b = normal.dot(vertices_b.at(0));
		max_b = min_b;

		for(unsigned int j = 1; j < vertices_b.size(); j++) {

			test = normal.dot(vertices_b.at(j));

			if(test < min_b)
				min_b = test;
			if(test > max_b)
				max_b = test;
		}

		offset = normal.dot(position_offset);

		min_a += offset;
		max_a += offset;

		test_1 = min_a - max_b;
		test_2 = min_b - max_a;

		if(test_1 > 0 || test_2 > 0) {
			flag = true;
			break;
		}
	}

	if(!flag) {
		double x = normal.at(0) * (-(max_b - min_a));
		double y = normal.at(1) * (-(max_b - min_a));

		cout << "Collision" << endl;

		return Vector(x, y);
	}
	else{
		cout << "-----" << endl;
		return Vector(0, 0);
	}
}