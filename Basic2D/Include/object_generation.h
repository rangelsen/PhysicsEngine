#ifndef OBJECT_GENERATION_H
#define OBJECT_GENERATION_H

#include <vector>

class Object;

std::vector<Object*> generate_test_objects();
std::vector<Object*> generate_convex_polygons(unsigned int n_polygons, unsigned int n_vertices);
std::vector<Object*> generate_test_objects_simple();

#endif
