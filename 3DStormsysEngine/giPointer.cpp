#include "giPointer.h"

giPointer::giPointer(point3d* pos, point3d *pointat)
{
	position = pos;
	myShape = shapes::newSphere(position, 0.0f);
	_pointAt = pointat;
	pitch = 0;
	yaw = 0;
	remove_me=false;
}
GameItemType giPointer::getType()
{
	return POINTER;
}
void giPointer::update(int timeElapsed)
{
	Rotation *r = getAngles(position,_pointAt);
	pitch = r->pitch;
	yaw = r->yaw;
}
void giPointer::render()
{	
		Rotation *r = getAngles(position,_pointAt);
		glPushMatrix();
			glTranslatef(position->x, position->y, position->z);			

			glPushMatrix();
				glRotatef(pitch, 0,0,1);

				glRotatef(yaw, 0,1,0);

				GLUquadricObj *quadObj = gluNewQuadric();
				gluQuadricDrawStyle(quadObj, GLU_FILL);
				gluQuadricNormals(quadObj, GLU_SMOOTH);
				gluQuadricOrientation(quadObj, GLU_OUTSIDE);

				glColor3f(0,0,1);
				gluCylinder(quadObj, 0.05f, 0.0f, 0.1f, 10, 10);

				glPushMatrix();
					glTranslatef(0,0,-0.1f);
					glColor3f(0,1,1);
					gluCylinder(quadObj, 0.02f, 0.02f, 0.1f, 10, 10);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
}
void giPointer::pointAt(point3d*pointat)
{
	_pointAt = pointat;
}
void giPointer::moveTo(point3d*move)
{
	position = move;
}