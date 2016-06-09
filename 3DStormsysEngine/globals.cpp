#include "globals.h"


float randFloat(float a, float b) {
	return ((b-a)*((float)rand()/RAND_MAX))+a;
} 
float degToRad(float deg)
{
	return deg*(PI/180.0f);
}
float radToDeg(float rad)
{
	return rad * (180.0f/3.14159f);
}
point3d *spherePoint(point3d *centre, float radius, float pitch, float heading)
{
	float _heading = degToRad(heading); 				
	float _pitch = degToRad(pitch); 
	float _x = radius * sin(_heading) * cos(_pitch);
	float _y = radius * sin(_pitch);
	float _z = radius * cos(_pitch) * cos(_heading);
	return new point3d(centre->x + _x, centre->y + _y, centre->z + _z);
}
float pointDistance(point3d *p1, point3d *p2)
{
	point3d *d = new point3d(p1->x - p2->x, p1->y - p2->y, p1->z - p2->z);
	return (float)sqrt(pow(d->x, 2) + pow(d->y, 2) + pow(d->z, 2));
}
void drawTorus(float r, float R, float nsides, float rings)
{
  int i, j;
  float theta, phi, theta1;
  float cosTheta, sinTheta;
  float cosTheta1, sinTheta1;
  float ringDelta, sideDelta;

  ringDelta = 2.0 * PI / rings;
  sideDelta = 2.0 * PI / nsides;

  theta = 0.0;
  cosTheta = 1.0;
  sinTheta = 0.0;
  for (i = 0; i < rings; i++) {
    theta1 = theta + ringDelta;
    cosTheta1 = cos(theta1);
    sinTheta1 = sin(theta1);
    glBegin(GL_QUAD_STRIP);
    phi = 0.0;
    for (j = 0; j < nsides + 1; j++) {
      GLfloat cosPhi, sinPhi, dist;

      phi += sideDelta;
      cosPhi = cos(phi);
      sinPhi = sin(phi);
      dist = R + r * cosPhi;
	  glTexCoord2f(1.0f - ((1.0f / rings) * (i)),((1.0f / nsides) * (j))); 
      glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
      glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
	  glTexCoord2f(1.0f - ((1.0f / rings) * (i+1)),((1.0f / nsides) * ( j))); 
		glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
      glVertex3f(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
	  
    }
    glEnd();
    theta = theta1;
    cosTheta = cosTheta1;
    sinTheta = sinTheta1;
  }
}
Rotation *getAngles(point3d *p1, point3d* p2)
{
	point3d *d = new point3d(p2->x - p1->x, p2->y - p1->y, p2->z - p1->z);

	float heading = radToDeg(atan2(d->x,d->z));
	float pitch =  radToDeg(atan2(d->y, sqrt( (d->x * d->x) + (d->z * d->z) )));
	if(d->x < 0)
			pitch *= -1;
	return new Rotation(heading, pitch, 0);
}
int randInt(int min, int max)
{	
	return (int)(rand()%(max-min))+min;
}
void printText(point3d *position, LPVOID font, char* text)
{ 
    if(!text || !strlen(text)) return; 
    glEnable(GL_BLEND); 
    glColor3f(1,1,1); 
    glRasterPos2f(position->x,position->y); 
    while (*text) { 
        glutBitmapCharacter(font, *text); 
        text++; 
    } 
}  