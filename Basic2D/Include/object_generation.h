#ifndef OBJECT_GENERATION_H
#define OBJECT_GENERATION_H

#include <vector>

class Object;

std::vector<Object*> OBJ_generate_test_objects();
std::vector<Object*> OBJ_generate_convex_polygons(unsigned int n_polygons, unsigned int n_vertices);
std::vector<Object*> OBJ_generate_test_objects_simple();
std::vector<Object*> OBJ_generate_test_objects_multiple();
Object* 			 OBJ_generate_rect(double w, double h);
Object*			     OBJ_generate_platform(double x, double);
void 				 OBJ_configure_objects_vertical(std::vector<Object*> objects); 
void 				 OBJ_configure_objects_horizontal(std::vector<Object*> objects); 

#endif
