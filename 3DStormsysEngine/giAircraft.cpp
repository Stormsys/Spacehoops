#include "giAircraft.h"

	GLfloat  model_specLight[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat  model_defuseLight[] = { 0.8f,  0.8f, 0.8f,  1.0f };
	GLfloat  model_ambiantLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat  model_spot_direction[] = { 0.0, 0.0, 0.0 };

	GLfloat  model_specLight_green[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat  model_spot_direction_green[] = { 0.0, 0.0, 0.0 };
	GLfloat  model_ambiantLight_green[] = { 0.2f, 0.4f, 0.2f, 1.0f };

	GLfloat	 model_lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat	 model_lightPos2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat model_shine[] = {128}; 
giAircraft::giAircraft()
{
	myModel = new ObjModel("f-16.obj");
	pitch = 0.0f;
	heading = 0.0f;
	roll = 0.0f;
	position = new point3d(-100.0f,0,0);
	pitchDest = 0;
	last_orient_update = 0;
	desired_turnSpeed = 0.0f;
	actual_turnSpeed = 0.0f;
	desired_tiltSpeed = 0.0f;
	actual_tiltSpeed = 0.0f;
	lightAngle = 0;
	myShape = shapes::newSphere(position, 1.7f);

	glLightfv(GL_LIGHT1,GL_POSITION,model_lightPos);	
	glLightfv(GL_LIGHT1,GL_SPECULAR,model_specLight_green);
	glLightfv(GL_LIGHT1,GL_AMBIENT,model_ambiantLight_green);		
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 2); // angle is 0 to 180
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128); // exponent is 0 to 128
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, model_spot_direction_green );
	glLightfv(GL_LIGHT1,GL_SHININESS,model_shine);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2,GL_AMBIENT,model_ambiantLight);	
	glLightfv(GL_LIGHT2,GL_POSITION,model_lightPos2);	
	glLightfv(GL_LIGHT2,GL_DIFFUSE,model_defuseLight);
	glLightfv(GL_LIGHT2,GL_SPECULAR,model_specLight);
	glLightfv(GL_LIGHT2,GL_SHININESS,model_shine);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, model_spot_direction );
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180); // angle is 0 to 180
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 128); // exponent is 0 to 128
	glEnable(GL_LIGHT2);

	remove_me=false;
}
GameItemType giAircraft::getType()
{
	return SPACECRAFT;
}
void giAircraft::update(int timeElapsed)
{
	if(last_orient_update + 10 < timeElapsed)
	{	
		float turn_acceleration = 0.02f;
		if(actual_turnSpeed > desired_turnSpeed)
		{
			actual_turnSpeed -= turn_acceleration;	
			if(actual_turnSpeed < desired_turnSpeed && desired_turnSpeed - actual_turnSpeed  < 0.02f)
				actual_turnSpeed = desired_turnSpeed;
		}
		else if(actual_turnSpeed < desired_turnSpeed)
		{
			actual_turnSpeed += turn_acceleration;		
			if(actual_turnSpeed > desired_turnSpeed && actual_turnSpeed - desired_turnSpeed < 0.02f)
				actual_turnSpeed = desired_turnSpeed;
		}

		heading += actual_turnSpeed;

		roll = actual_turnSpeed * -50.0f; //roll of 50 is akin to max speed, like realistic spacecraft
		

	
		if(actual_tiltSpeed > desired_tiltSpeed)
		{
			actual_tiltSpeed -= turn_acceleration;	
			if(actual_tiltSpeed < desired_tiltSpeed && desired_tiltSpeed - actual_tiltSpeed  < 0.05f)
				actual_tiltSpeed = desired_tiltSpeed;
		}
		else if(actual_tiltSpeed < desired_tiltSpeed)
		{
			actual_tiltSpeed += turn_acceleration;		
			if(actual_tiltSpeed > desired_tiltSpeed && actual_tiltSpeed - desired_tiltSpeed < 0.05f)
				actual_tiltSpeed = desired_tiltSpeed;
		}
		pitch += actual_tiltSpeed;
		if(pitch > 70 || pitch < -70)
		{
				desired_tiltSpeed = 0;
				actual_tiltSpeed = 0;

				if(pitch > 70)
					pitch = 70;
				else
					pitch = -70;
		}

		//move spacecraft forward
		position = spherePoint(position, 0.4f, pitch,  heading + 90);


		lightAngle++;
		if(lightAngle >= 360)
			lightAngle = lightAngle - 360; 

		model_lightPos[0] = position->x + cos(degToRad(lightAngle))*6.0f;
		model_lightPos[1] = position->y + 0.5f;
		model_lightPos[2] = position->z + sin(degToRad(lightAngle))*6.0f;
		point3d *dir_green =  new point3d(position->x - model_lightPos[0], position->y - model_lightPos[1], position->z - model_lightPos[2]);
		model_spot_direction_green[0] = dir_green->x;
		model_spot_direction_green[1] = dir_green->y;
		model_spot_direction_green[2] = dir_green->z;

		point3d *lightPos = spherePoint(position, 15.0f,370 - pitch,  heading -90);
		model_lightPos2[0] = lightPos->x;
		model_lightPos2[1] = lightPos->y;
		model_lightPos2[2] = lightPos->z;

		point3d *direction =  new point3d(position->x - lightPos->x, position->y - lightPos->y, position->z - lightPos->z);
		
		model_spot_direction[0] = direction->x;
		model_spot_direction[1] = direction->y;
		model_spot_direction[2] = direction->z;


		myShape->location = position;

		last_orient_update = timeElapsed;
	}
}
void giAircraft::render()
{
	

	glLightfv(GL_LIGHT1,GL_POSITION,model_lightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, model_spot_direction_green );
	glLightfv(GL_LIGHT2,GL_POSITION,model_lightPos2);	
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, model_spot_direction );

	glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
		glRotatef(heading, 0,1,0);

		glPushMatrix();
			glRotatef(pitch, 0,0,1);
			glRotatef(roll, 1,0,0);
			glScalef(0.5f, 0.5f, 0.5f);
			myModel->drawModel();
		glPopMatrix();
		
		if(ENGINE_DEBUG){
				glColor3f(0.0f,0.0f,1.0f);
				GLUquadricObj *sheildSphere = gluNewQuadric();
				gluQuadricDrawStyle(sheildSphere, GLU_LINE);
				gluQuadricTexture(sheildSphere, true);
				gluQuadricNormals(sheildSphere, GLU_SMOOTH);
				gluQuadricOrientation(sheildSphere, GLU_OUTSIDE);
	
				gluSphere(sheildSphere,1.7f,50,35);
		}
	/*	glColor3f(0.0f,0.0f,1.0f);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,-0.05f);
			glVertex3f(0.0f,1.0f,-0.05f);
			glVertex3f(0.0f,0.0f,0.05f);
			glVertex3f(0.0f,1.0f,0.05f);

			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(2.0f,-0.4f,-2.0f);
			glVertex3f(2.0f,-0.4f,2.0f);

			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-2.0f,-0.7f,-2.0f);
			glVertex3f(-2.0f,-0.7f,2.0f);
		glEnd();
		glEnable(GL_LIGHTING);*/
	glPopMatrix();
}

void giAircraft::turnMaxSpeedAdd(float num)
{
	//can only be between -1 and 1, used as percentage
		desired_turnSpeed += num;
		if(desired_turnSpeed > 1.0f)
			desired_turnSpeed = 1.0f;
		else if(desired_turnSpeed < -1.0f)
			desired_turnSpeed = -1.0f;
		
}
void giAircraft::tiltMaxSpeedAdd(float num)
{
		desired_tiltSpeed += num;
		if(desired_tiltSpeed > 0.5f)
			desired_tiltSpeed = 0.5f;
		else if(desired_tiltSpeed < -0.5f)
			desired_tiltSpeed = -0.5f;
}