#include "giSkybox.h"

giSkybox::giSkybox()
{
	position = new point3d(0,0,0);
	last_rot_elapsed = 0;
	last_change_elapsed = 0;
	rotx = 0.0f;
	roty = 0.0f;
	rotz = 0.0f;
	changex = randFloat(-0.05f, 0.05f);
	changey = randFloat(-0.05f, 0.05f);
	changez = randFloat(-0.05f, 0.05f);
	myShape = shapes::newSphere(position, 200.0f);
	remove_me=false;
}
GameItemType giSkybox::getType()
{
	return SKYBOX;
}
void giSkybox::render()
{
	glColor3f(1,1,1);
	glDisable(GL_LIGHTING);
	Textures::Use(TEXTURE_SKYBOX);	
				GLUquadricObj *skyBoxSphere = gluNewQuadric();
				gluQuadricDrawStyle(skyBoxSphere, GLU_FILL);
				gluQuadricTexture(skyBoxSphere, true);
				gluQuadricNormals(skyBoxSphere, GLU_SMOOTH);
				gluQuadricOrientation(skyBoxSphere, GLU_INSIDE);
				

				glPushMatrix();
				glRotatef(rotx,1,0,0);
				glRotatef(roty,0,1,0);
				glRotatef(rotz,0,0,1);

				gluSphere(skyBoxSphere,200.0f,50,35);

				glPopMatrix();
	Textures::Done();	
	glEnable(GL_LIGHTING);
}
void giSkybox::update(int timeElapsed)
{
	if(last_rot_elapsed + 10 < timeElapsed)
	{		
		rotx += changex;	
		roty += changey;	
		rotz += changez;
		last_rot_elapsed = timeElapsed;
	}
	if(last_change_elapsed + 5000 < timeElapsed)
	{		
		changex = randFloat(-0.05f, 0.05f);
		changey = randFloat(-0.05f, 0.05f);
		changez = randFloat(-0.05f, 0.05f);
		
		last_change_elapsed = timeElapsed;
	}
}