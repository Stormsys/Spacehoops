#ifndef GEOMETRY_H
#define GEOMETRY_H

class point3d
{
public:
	float x,y,z;
	point3d(float x, float y, float z);
};

class size3d
{
public:
	float w,h,d;
	size3d(float w, float h, float d);
};

class Color
{
public:
	Color(float r, float b, float g);
	float r,b,g;
};
class Rotation
{
public:
	Rotation(float y, float p, float r);
	float yaw,pitch,roll;
};
#endif