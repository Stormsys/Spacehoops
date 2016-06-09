#include "giHoop.h"
giHoop::giHoop(point3d *loc, float r, float cs_r, float ry, float rotation_speed)
{
	position = loc;

	radius = r;
	cs_radius = cs_r;
	roty = ry;

	rot_speed = rotation_speed;

	selected = false;

	remove_me=false;

	last_rot_elapsed = 0;
	myShape = shapes::newTorus(position, radius, cs_radius, roty - 90);
}
GameItemType giHoop::getType()
{
	return HOOP;
}

void giHoop::render()
{	
	glDisable(GL_LIGHTING);
	if(selected)
		Textures::Use(TEXTURE_HOOPS_S);
	else
		Textures::Use(TEXTURE_HOOPS);	

	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(position->x,position->y,position->z);
	glRotatef(roty, 0,1,0);
	drawTorus(cs_radius, radius, 10, 100);

	glPopMatrix();
	Textures::Done();
	glEnable(GL_LIGHTING);

}

void giHoop::update(int timeElapsed)
{
	if(last_rot_elapsed + 50 < timeElapsed)
	{	
		roty += rot_speed;
		if(roty > 360)
			roty-=360;
			myShape->roty = roty;
		last_rot_elapsed = timeElapsed;
	}
}