#include "HUD.h"
#include "textures.h"
#define RadarSize 140.0f
#define RadarOffset 10.0f
#define LifeBarW 668.0f
#define LifeBarH 30.0f
static int current_health = 0;
static int current_sheild = 0;
static int animation = 0;
void HUD::animateSheildHealth(float hull, float life)
{
	int timeElapsed = glutGet(GLUT_ELAPSED_TIME);
	if(animation + 10 < timeElapsed)
	{
		if(hull > current_sheild)
			current_sheild++;
		else if(hull < current_sheild)
			current_sheild--;

		if(life > current_health)
			current_health++;
		else if(life < current_health)
			current_health--;
		animation  = timeElapsed;
	}
}
void HUD::drawSheild()
{
	int shield_per = current_sheild;
			glPushMatrix();
			glTranslatef(47.0f,1.0f,0);			
				Textures::Use(TEXTURE_HUD_SHEILD);	
				glBegin(GL_QUADS);	
					glTexCoord2f(0,(shield_per/100.0f));
					glVertex2f((shield_per/100.0f)*182.0f,-7.0f);
					glTexCoord2f(0,0);
					glVertex2f((shield_per/100.0f)*182.0f,7.0f);
					glTexCoord2f((shield_per/100.0f),0);
					glVertex2f(0.0f,7.0f);
					glTexCoord2f((shield_per/100.0f),(shield_per/100.0f));
					glVertex2f(0.0f,-7.0f);
				glEnd();
				Textures::Done();	
			glPopMatrix();
}
void HUD::drawHealth()
{	
	int health_per = current_health;
			glPushMatrix();
			glTranslatef(-47.0f,1.0f,0);			
				Textures::Use(TEXTURE_HUD_HEALTH);	
				glBegin(GL_QUADS);	
					glTexCoord2f(0,(health_per/100.0f));
					glVertex2f((health_per/100.0f)*-182.0f,-7.0f);
					glTexCoord2f(0,0);
					glVertex2f((health_per/100.0f)*-182.0f,7.0f);
					glTexCoord2f((health_per/100.0f),0);
					glVertex2f(0.0f,7.0f);
					glTexCoord2f((health_per/100.0f),(health_per/100.0f));
					glVertex2f(0.0f,-7.0f);
				glEnd();
				Textures::Done();	
			glPopMatrix();
}
void HUD::drawLifeBar(float windowWidth, float windowHeight, float hull, float life)
{
	glColor4f(1,1,1,0);
	glPushMatrix();
		glTranslatef((windowWidth/2.0f), windowHeight - (LifeBarH*2.0f), 0.0f);

		
			Textures::Use(TEXTURE_SCORE_ORB);
			glBegin(GL_POLYGON);//Radar
				for (float i=0; i < 360.0f; i++)
				{
					float x =  ((cos(degToRad(i))  + 1.0f)/ 2.0f);
					float y = 1.0f -((sin(degToRad(i)) + 1.0f) / 2.0f);	
					glTexCoord2f(x,y);

					x = cos(degToRad(i));
					y = sin(degToRad(i));
					glVertex2f(x*48.0f,y*48.0f);
				}
			glEnd();
			Textures::Done();
	

			animateSheildHealth(hull, life);
			drawSheild();
			drawHealth();

		Textures::Use(TEXTURE_HUD_LIFEBAR);	
		glBegin(GL_QUADS);			
			glTexCoord2f(0,1);
			glVertex2f(-(LifeBarW/2.0f),-(LifeBarH/2.0f));
			glTexCoord2f(0,0);
			glVertex2f(-(LifeBarW/2.0f),(LifeBarH/2.0f));
			glTexCoord2f(1,0);
			glVertex2f((LifeBarW/2.0f),(LifeBarH/2.0f));
			glTexCoord2f(1,1);
			glVertex2f((LifeBarW/2.0f),-(LifeBarH/2.0f));
		glEnd();
		Textures::Done();	
	glPopMatrix();
}
void HUD::drawStaticIndicators(giAircraft *aircraft, float windowWidth, float windowHeight)
{
	glBegin(GL_LINES);
		//Speed Iniators
		glColor3f(0.29f, 0.3f, 0.0f);
		glVertex2f(windowWidth /2.0f, windowHeight / 2.0f - 175.0f);// center arc
		glVertex2f(windowWidth /2.0f, windowHeight / 2.0f - 190.0f);// center arc		
	
	glEnd();

	/*level and tilt indicators*/
	glPushMatrix();		
		glTranslatef(windowWidth /2.0f, windowHeight / 2.0f, 0);			
		glBegin(GL_LINES);		
			glColor4f(0.29f, 1.0f, 0.0f, 0.2f);
			glVertex2f(-250.0f, 0.0f);
			glVertex2f(-200.0f, 0.0f); 
			glVertex2f(250.0f, 0.0f);
			glVertex2f(200.0f, 0.0f);
			
			glColor3f(0.79f, 1.0f, 0.0f);
			/*level speed*/
			glVertex2f(-250.0f, -aircraft->desired_tiltSpeed * 50.0f); 
			glVertex2f(-200.0f, -aircraft->desired_tiltSpeed * 50.0f); 
			glVertex2f(250.0f, -aircraft->desired_tiltSpeed * 50.0f);
			glVertex2f(200.0f, -aircraft->desired_tiltSpeed * 50.0f);	
		glEnd();
	glPopMatrix();
	
	/* tilt inidcator */
	glPushMatrix();
		glTranslatef(windowWidth /2.0f, (windowHeight / 2.0f) -100.0f, 0);
		glBegin(GL_LINES);
			glColor3f(0.29f, 1.0f, 0.0f);
			glVertex2f(0, -50.0f);
			glVertex2f(cos(degToRad((aircraft->actual_turnSpeed * -45.0f)-90.0f))*70.0f,sin(degToRad((aircraft->actual_turnSpeed * -45.0f)-90.0f))*70.0f);
						
			glColor3f(0.79f, 1.0f, 0.0f);
			glVertex2f(0, -50.0f);
			glVertex2f(cos(degToRad((aircraft->desired_turnSpeed * -45.0f)-90.0f))*70.0f,sin(degToRad((aircraft->desired_turnSpeed * -45.0f)-90.0f))*70.0f);
		glEnd();
	glPopMatrix();
}
void HUD::drawLevelIndicators(giAircraft *aircraft, float windowWidth, float windowHeight)
{
	glPushMatrix();
		glTranslatef(windowWidth /2.0f, windowHeight / 2.0f + aircraft->pitch, 0.0f);
		glBegin(GL_LINES);		
			glColor3f(0.29f, 1.0f, 0.0f);
			/*middle-Level Indicators*/
			glVertex2f(-260.0f, -3.0f); 
			glVertex2f(-240.0f, -3.0f); 
			glVertex2f(260.0f, -3.0f); 
			glVertex2f(240.0f, -3.0f); 
			glVertex2f(-260.0f, 3.0f); 
			glVertex2f(-240.0f, 3.0f);
			glVertex2f(260.0f, 3.0f); 
			glVertex2f(240.0f, 3.0f); 
			
			glColor3f(0.29f, 0.6f, 0.0f);
			float windowStep = ((windowHeight / 2.0f - 3.0f) - (windowHeight / 2.0f - 70.0f)) / 10.0f;
			for(unsigned int i = 1; i < 10; i++)
			{
				/* right step-level indicators top */
				glVertex2f(260.0f, -(70.0f - (windowStep * i))); 
				glVertex2f(250.0f, -(70.0f - (windowStep * i))); 
				/* right step-level indicators bottom */
				glVertex2f(260.0f, (70.0f - (windowStep * i))); 
				glVertex2f(250.0f, (70.0f - (windowStep * i))); 				
				/* left step-level indicators top */
				glVertex2f(-260.0f, -(70.0f - (windowStep * i))); 
				glVertex2f(-250.0f, -(70.0f - (windowStep * i))); 
				/* left step-level indicators bottom */
				glVertex2f(-260.0f, (70.0f - (windowStep * i))); 
				glVertex2f(-250.0f, (70.0f - (windowStep * i))); 
			}

			glColor3f(1.0f, 0.14f, 0.0f);
			glVertex2f(260.0f, 70.0f); //max-min indicators
			glVertex2f(240.0f, 70.0f); //max-min indicators
			glVertex2f(260.0f, -70.0f); //max-min indicators
			glVertex2f(240.0f, -70.0f); //max-min indicators
			glVertex2f(-260.0f, -70.0f); //max-min indicators
			glVertex2f(-240.0f, -70.0f); //max-min indicators
			glVertex2f(-260.0f, 70.0f); //max-min indicators
			glVertex2f(-240.0f, 70.0f); //max-min indicators
		glEnd();	
	glPopMatrix();
}
void HUD::drawArc(float windowWidth, float windowHeight)
{	
	glPushMatrix();
	glTranslatef(windowWidth /2.0f, (windowHeight / 2.0f) - 100.0f, 0);	
		glColor3f(0.29f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
			for (float i=225.0f; i < 225.0f+90.0f; i+= 3)
			{
				float radius = 80.0f;
				glVertex2f(cos(degToRad(i))*radius,sin(degToRad(i))*radius); //Level arc, / turn speed indicator
			}	
		glEnd();
	glPopMatrix();
}
void HUD::drawHUD(giAircraft * aircraft, float windowWidth, float windowHeight, float sheild, float life)
{
	drawStaticIndicators(aircraft, windowWidth, windowHeight);
	drawArc(windowWidth, windowHeight);
	drawLevelIndicators(aircraft, windowWidth, windowHeight);
	drawLifeBar( windowWidth, windowHeight, sheild, life);
}


void HUD::drawMMSpaceship(giAircraft * aircraft)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	Textures::Use(TEXTURE_MINIMAP_SPACECRAFT);
	glPushMatrix();
		glTranslatef((aircraft->position->x / 4) + (RadarOffset + (RadarSize/2)),(aircraft->position->z / 4) + (RadarOffset + (RadarSize/2)), 0);
		glPushMatrix();
			glRotatef(-aircraft->heading + 90, 0,0,1);
			glBegin(GL_TRIANGLES);
				glTexCoord2f(1.0f,0.0f);
				glVertex2f(6.0f,12.0f);
				glTexCoord2f(0.5f,1.0f);
				glVertex2f(0.0f,0.0f);				
				glTexCoord2f(0.0f,0.0f);
				glVertex2f(-6.0f,12.0f);
			glEnd();
		glPopMatrix();
	glPopMatrix();		
	Textures::Done();
}
void HUD::plotMMHoops(vector<CrystalLink *> crystals)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
			for (int i=0; i < crystals.size(); i++)
			{
				if(i==0)
					glColor3f(0.0f, 1.0f, 0.0f);
				else
					glColor3f(1.0f, 1.0f, 0.0f);
				glVertex2f((crystals[i]->hoop->position->x / 4) + (RadarOffset + (RadarSize/2)),(crystals[i]->hoop->position->z / 4)+ (RadarOffset + (RadarSize/2)));
			}
	glEnd();
}
void HUD::drawRadarBack()
{
	/*
	glColor3f(0.0f, 0.8f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(RadarOffset + (RadarSize/2),RadarOffset);//Cross Lines
		glVertex2f(RadarOffset + (RadarSize/2),RadarOffset + RadarSize);//Cross Lines

		glVertex2f(RadarOffset,RadarOffset + (RadarSize/2));//Cross Lines
		glVertex2f(RadarOffset + RadarSize,RadarOffset + (RadarSize/2));//Cross Lines
	glEnd();
	*/
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	
	Textures::Use(TEXTURE_MINIMAP);
	glPushMatrix();
	glTranslatef(RadarOffset,RadarOffset,0);
	glBegin(GL_POLYGON);//Radar
		for (float i=0; i < 360.0f; i++)
		{
			float x =  ((cos(degToRad(i))  + 1.0f)/ 2.0f);
			float y = 1.0f -((sin(degToRad(i)) + 1.0f) / 2.0f);	
			glTexCoord2f(x,y);

			x = ((cos(degToRad(i))  + 1.0f)/ 2.0f);
			y = ((sin(degToRad(i)) + 1.0f) / 2.0f);
			glVertex2f(x*RadarSize,y*RadarSize);
		}
	glEnd();
	glPopMatrix();
	Textures::Done();
}
void HUD::drawRadar(giAircraft * aircraft, vector<CrystalLink *> crystals)
{
	glPointSize(2.5f);
	drawMMSpaceship(aircraft);
	plotMMHoops(crystals);
	drawRadarBack();
}