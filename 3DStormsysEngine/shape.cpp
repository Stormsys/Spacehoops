#include "shape.h"

shape::shape(point3d *in_location, float in_radius, ShapeType in_type, float in_csRadius, float in_roty)
{
	location = in_location;
	radius = in_radius;
	type = in_type;
	roty = in_roty;
	csRadius = in_csRadius;
}

shape::shape(point3d *in_location, float in_radius, ShapeType in_type)
{
	location = in_location;
	radius = in_radius;
	type = in_type;
}
shape::shape(point3d *in_location, size3d *in_size, ShapeType in_type)
{	
	location = in_location;
	size = in_size;
	type = in_type;
	updatePlotList();
}
void shape::moveUp(float i)
{
	location->y += i;
	updatePlotList();
}
void shape::moveDown(float i)
{	
	location->y -= i;
	updatePlotList();
}
void shape::moveLeft(float i)
{
	location->x -= i;
	updatePlotList();
}
void shape::moveRight(float i)
{
	location->x += i;
	updatePlotList();
}
void shape::moveFront(float i)
{
	location->z -= i;
	updatePlotList();
}
void shape::moveBack(float i)
{
	location->z += i;
	updatePlotList();
}

void shape::updatePlotList()
{
	plot_list.clear();
	//todo
	if(type == AP_BOX)
	{
		//face 1
		plot_list.push_back(new point3d(location->x, location->y, location->z));
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z));
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z));

		//face 2
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x, location->y, location->z + size->d));

		//face 3		
		plot_list.push_back(new point3d(location->x, location->y, location->z));
		plot_list.push_back(new point3d(location->x, location->y, location->z + size->d));
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z));
		
		//face 4	
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z));
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z));

		//face 5		
		plot_list.push_back(new point3d(location->x, location->y, location->z));
		plot_list.push_back(new point3d(location->x, location->y, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y, location->z));
		
		//face 6		
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z));
		plot_list.push_back(new point3d(location->x, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z + size->d));
		plot_list.push_back(new point3d(location->x + size->w, location->y + size->h, location->z));
	}
}

shape *shapes::newBox(point3d *location, size3d *size)
{
	return new shape(location, size, AP_BOX);
}
shape *shapes::newSphere(point3d *location, float radius)
{
	return new shape(location, radius, SPHERE);
}
shape *shapes::newTorus(point3d *location, float radius, float csRadius, float rotz)
{
	return new shape(location, radius, UR_TORUS, csRadius, rotz);
}
void shapes::drawShape(shape *sShape)
{
	if(sShape->type == AP_BOX)
	{
		glBegin(GL_QUADS);
			for(unsigned int i = 0; i < sShape->plot_list.size(); i++)
			{
				glVertex3f(sShape->plot_list[i]->x,sShape->plot_list[i]->y,sShape->plot_list[i]->z);
			}
		glEnd();
	}
}