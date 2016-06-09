#ifndef SHAPE_H
#define SHAPE_H
#include "shared/gltools.h"

#include "globals.h"
#include "geometry.h"
#include <vector>

class shape
{
public:
	point3d *location;
	size3d *size;
	float radius;
	float csRadius;
	float roty;
	ShapeType type;

	shape(point3d *location, float radius, ShapeType type);
	shape(point3d *location, size3d *size, ShapeType type);
	shape(point3d *location, float radius, ShapeType type, float csRadius, float roty);

	void moveUp(float i);
	void moveDown(float i);
	void moveLeft(float i);
	void moveRight(float i);
	void moveFront(float i);
	void moveBack(float i);

	std::vector<point3d *> plot_list;
private:
	
	void updatePlotList();
};

class shapes
{
public:
	static shape *newBox(point3d *location, size3d *size);
	static shape *newSphere(point3d *location, float radius);
	static shape *newTorus(point3d *location, float radius, float csRadius, float roty);
	static void drawShape(shape *Shape);
};


#endif