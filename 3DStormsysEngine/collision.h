#ifndef COLLISION_H
#define COLLISION_H

#include "shape.h"

class collision
{
public:
	static bool collides(shape *s1, shape* s2);	
	static bool collides_sphere_sphere_edge(shape *s1, shape* s2);
private:
	static bool collides_box_box(shape *s1, shape* s2);
	static bool collides_sphere_sphere(shape *s1, shape* s2);
	static bool collides_sphere_torus(shape *s1, shape* s2);
};



#endif