#ifndef CAMERA_H
#define CAMERA_H
#include "shared/gltools.h"

#include "geometry.h"

class camera
{
public:
	camera(point3d *loc, point3d *lookat,int w, int h);
	void movePosition(point3d *loc);
	void moveTarget(point3d *loc);
	void changeWindowSize(int w, int h);
	void update();
	point3d *location;
private:
	
	point3d *destination;
	int windowHeight,windowWidth;
	float perspectiveAngle, zNear, zFar, aspectRatio;
};
#endif