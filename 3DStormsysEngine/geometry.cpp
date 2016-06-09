#include "geometry.h"

size3d::size3d(float a, float b, float c)
{
	w = a;
	h = b;
	d = c;
}
point3d::point3d(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Color::Color(float ir, float ib, float ig)
{
	r = ir;
	b = ib;
	g = ig;
}
Rotation::Rotation(float _y, float _p, float _r)
{
	yaw = _y;
	pitch = _p;
	roll = _r;
}