#include "camera.h"

camera::camera(point3d *loc, point3d *lookat,int w, int h)
{
	location = loc;
	destination = lookat;
	windowHeight = h;
	windowWidth = w;
	perspectiveAngle = 45.0f;
	zNear = 1;
	zFar = 1300;
	aspectRatio = (float)windowWidth/(float)windowHeight;
}
void camera::movePosition(point3d *loc)
{
	location = loc;
}
void camera::moveTarget(point3d *loc)
{
	destination = loc;
}
void camera::changeWindowSize(int w, int h)
{	
	windowHeight = h;
	windowWidth = w;	
	aspectRatio = (float)w/(float)h;
}
void camera::update()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(perspectiveAngle, aspectRatio, zNear, zFar);

	gluLookAt(location->x,location->y,location->z,destination->x,destination->y,destination->z,0,1,0);
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}