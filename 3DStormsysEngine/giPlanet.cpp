#include "giPlanet.h"
giPlanet::giPlanet(float rad_planet, float rad_dist, point3d * rot, point3d *orbit)
{
	position = new point3d(0,0,0);
	last_rot_elapsed = 0;
	rotx = 0;
	roty = 0;
	rotz = 0;
	orbitx = 0;
	orbity = 0;
	orbitz = 0;
	rotx_speed = rot->x;
	roty_speed = rot->y; 
	rotz_speed = rot->z;
	orb_y_speed = orbit->y;
	orb_z_speed = orbit->z;
	orbit_radius = rad_dist;
	planet_radius = rad_planet;
	myShape = shapes::newSphere(position, rad_planet);
	remove_me=false;
	planet = randInt(TEXTURE_PLANET_START, TEXTURE_PLANET_END+1);
	cout << planet << endl;
}
GameItemType giPlanet::getType()
{
	return PLANET;
}
void giPlanet::render()
{
	Textures::Use(planet);	
				GLUquadricObj *sunSphere = gluNewQuadric();
				gluQuadricDrawStyle(sunSphere, GLU_FILL);
				gluQuadricTexture(sunSphere, true);
				gluQuadricNormals(sunSphere, GLU_SMOOTH);
				gluQuadricOrientation(sunSphere, GLU_OUTSIDE);
				

				glPushMatrix();
				glTranslatef(position->x, position->y, position->z);
				glRotatef(rotx,1,0,0);
				glRotatef(roty,0,1,0);
				glRotatef(rotz,0,0,1);

				gluSphere(sunSphere,planet_radius,50,35);

				glPopMatrix();
	Textures::Done();	
}
void giPlanet::update(int timeElapsed)
{
	if(last_rot_elapsed + 10 < timeElapsed)
	{		
			orbity += orb_y_speed;
			if(orbity>360) orbity-=360;
			orbitz += orb_z_speed;
			if(orbitz>360) orbitz-=360;


			roty += roty_speed;
			if(roty>360) roty-=360;
			rotz += rotz_speed;
			if(roty>360) roty-=360;	
			rotx += rotx_speed;
			if(rotx>360) rotx-=360;

			position = spherePoint(new point3d(0,0,0), orbit_radius, orbity,orbitz);
			myShape = shapes::newSphere(position, planet_radius);

			last_rot_elapsed = timeElapsed;
	}
	
}