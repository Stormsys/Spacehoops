#include "giSun.h"
giSun::giSun()
{
	position = new point3d(0,0,0);
	last_rot_elapsed = 0;
	rotx = 0.0f;
	roty = 0.0f;
	rotz = 0.0f;
	myShape = shapes::newSphere(position, 6.0f);
	remove_me=false;
}
GameItemType giSun::getType()
{
	return PLANET;
}
void giSun::render()
{
	glDisable(GL_LIGHTING);
	Textures::Use(TEXTURE_SUN);	
				GLUquadricObj *sunSphere = gluNewQuadric();
				gluQuadricDrawStyle(sunSphere, GLU_FILL);
				gluQuadricTexture(sunSphere, true);
				gluQuadricNormals(sunSphere, GLU_SMOOTH);
				gluQuadricOrientation(sunSphere, GLU_OUTSIDE);
				

				glPushMatrix();
				glRotatef(rotx,1,0,0);
				glRotatef(roty,0,1,0);
				glRotatef(rotz,0,0,1);

				gluSphere(sunSphere,6.0f,50,35);

				glPopMatrix();
	Textures::Done();	
	glEnable(GL_LIGHTING);
}
void giSun::update(int timeElapsed)
{
	if(last_rot_elapsed + 10 < timeElapsed)
	{		
		rotx += 0.5f;	
		roty += 0.5f;	
		rotz -= 0.5f;
		if(rotx >= 360)
			rotx = 0.0f;
		if(roty >= 360)
			roty = 0.0f;
		if(rotz >= 360)
			rotz = 0.0f;
		last_rot_elapsed = timeElapsed;
	}
	
}