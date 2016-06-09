#include "giCrystal.h"
giCrystal::giCrystal(point3d *loc)
{
	position = loc;
	myShape = shapes::newSphere(position, 3.2f);
	myModel = new ObjModel("diamond.obj");
	remove_me=false;
}
GameItemType giCrystal::getType()
{
	return CRYSTAL;
}

void giCrystal::render()
{	
	glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
		myModel->drawModel();
	glPopMatrix();
}

void giCrystal::update(int timeElapsed)
{

}