#include "gameEngine.h"
giAircraft *spacecraft = NULL;

void damage(int damage_amt)
{
	if(hull - damage_amt/4 >= 0)
	{

		hull -= damage_amt/2;
		life -= damage_amt/4;
	}else{
		life -= hull/4;
		life -= (damage_amt - hull);
		hull = 0;
	}
	if(hull < 0)
		hull = 0;
	if(life < 0)
		life = 0;
	/*each hitpoint of the hull/sheild mitigates 1/4 of the damae+1)*/
}
int main(int argc, char** argv)
{
	cout << endl;
	cout << "                ### ###    #   #### #### #  # #### #### ###   ###"  <<  endl;
	cout << "               #    #  #  # #  #  # #    #  # #  # #  # #  # #" <<  endl;
	cout << "                ##  ###  #   # #    #### #### #  # #  # ###  ###" <<  endl;
	cout << "                  # #    ##### #  # #    #  # #  # #  # #       #" <<  endl;
	cout << "               ###  #    #   # #### #### #  # #### #### #    ### " <<  endl;
	cout << "                                               +----------------+" <<  endl;
	cout << "                                               I by Diogo Moura I" <<  endl;
	cout << "                                               +----------------+" <<  endl;
	cout << endl << endl;

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_RGBA | GLUT_DEPTH  );
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition (500, 100);
	glutCreateWindow ("Stormsys 3D Engine");

	init();

	glutDisplayFunc(render);
    glutReshapeFunc(resize);

	glutSetCursor(GLUT_CURSOR_NONE); 
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(keyDown);	
	glutSpecialFunc(keyDownSpec);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(1,update,1);
	glutFullScreen();

	glutMainLoop();
	return 0;
}
void init(void)
{
	srand ( (int)time(NULL) );

	glFrontFace(GL_CCW);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambiantLight);	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambiantLight);	
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);	
	glLightfv(GL_LIGHT0,GL_DIFFUSE,defuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specLight);
	glEnable(GL_LIGHT0);


	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);
	glEnable (GL_LINE_SMOOTH);		
	glEnable( GL_POINT_SMOOTH );
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	Textures::LoadAll();

	life = 100;
	hull = 100;
	score = 0;
	gameover = false;

	glClearColor(0.0f, 0.0f, 0.05f, 1.0f );
	mainCamera = new camera(new point3d(-10,0,0), new point3d(0,0,0), windowWidth, windowHeight);
	thirdCameras[0] = new camera(new point3d(0, 100, 0), new point3d(0,0,0), windowWidth, windowHeight);
	thirdCameras[1] = new camera(new point3d(100, 0, 0), new point3d(0,0,0), windowWidth, windowHeight);
	thirdCameras[2] = new camera(new point3d(0, 0, 100), new point3d(0,0,0), windowWidth, windowHeight);
	thirdCameras[3] = new camera(new point3d(-100, 0, 0), new point3d(0,0,0), windowWidth, windowHeight);

	giList.clear();
	ch_list.clear();

	giList.push_back(new giSun());
	generatePlanets(6);
	giList.push_back(new giSkybox());
	giList.push_back(new giPointer(new point3d(0,0,0),new point3d(0,0,0) ));
	spacecraft = new giAircraft();
	giList.push_back(spacecraft);
	generateHoops(6);
}
void renderHUD()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	HUD::drawHUD(spacecraft, windowWidth, windowHeight, hull, life);
	HUD::drawRadar(spacecraft, ch_list);
}
void render(void)
{	
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f); 

		for(unsigned int i = 0; i < giList.size(); i++)
		{
			giList[i]->render();
		}

		if(ENGINE_DEBUG)
		{
				glBegin(GL_LINES);
				//y axis	
					glColor3f(0,1,0);
					glVertex3f(0,0,0);
					glVertex3f(0,20,0);

				//x axis	
					glColor3f(1,0,0);
					glVertex3f(0,0,0);
					glVertex3f(20,0,0);
					
				//z axis	
					glColor3f(0,0,1);
					glVertex3f(0,0,0);
					glVertex3f(0,0,20);
				glEnd();
		}
		if(chasecamera)
		{
				renderHUD();
		}
	glutSwapBuffers();
}
void keyDownSpec(int key, int x, int y)
{ 
}
void keyDown(unsigned char key, int x, int y)
{
  switch (key)
  {
	case 27:   
	  exit (0);
	  break;	
	  case '1':
	  case '!':
		if(!chasecamera)
			thirdCameraSelection = 0;
		break;
	case '2':
	case '"':
		if(!chasecamera)
			thirdCameraSelection = 1;
		break;
	case '3':
	case '£':
		if(!chasecamera)
			thirdCameraSelection = 2;
		break;
	case '4':
	case '$':
		if(!chasecamera)
			thirdCameraSelection = 3;
		break;
	case 'c':
		chasecamera = !chasecamera;
		Keyboard::UP = false;
		Keyboard::DOWN = false;
		Keyboard::LEFT = false;
		Keyboard::RIGHT = false;
		break;
	case 'W':
	case 'w':
			Keyboard::UP = true;
		break;
	case 'S':
	case 's':
			Keyboard::DOWN = true;
		break;
	case 'A':
	case 'a':
			Keyboard::LEFT = true;
		break;
	case 'D':
	case 'd':
			Keyboard::RIGHT = true;
			break;
	case 'P':
	case 'p':
		if(gameover)
			init();
		break;
  }
}
void keyUp(unsigned char key, int x, int y)
{  
  switch (key)
  {
	case 'W':
	case 'w':
			Keyboard::UP = false;
		break;
	case 'S':
	case 's':
			Keyboard::DOWN = false;
		break;
	case 'A':
	case 'a':
			Keyboard::LEFT = false;
		break;
	case 'd':
	case 'D':
			Keyboard::RIGHT = false;
		break;
  }
}
void mouseMove(int x, int y)
{
	if(chasecamera && !gameover)
	{
		if(windowWidth/2!= x && windowHeight/2 != y)
		{
 			float pitchChange = ((float)(y - windowHeight/2) / (float)windowHeight );
			float headingChange = ((float)(x - windowWidth/2) / (float)windowWidth );


			spacecraft->turnMaxSpeedAdd(-headingChange);
			spacecraft->tiltMaxSpeedAdd(-pitchChange);
		}
	}
}
void chRemove(GameItem *item)
{
		for(unsigned int i = 0; i < ch_list.size(); i++)
		{
				if(ch_list[i]->hoop == item || ch_list[i]->crystal == item)
				{
					ch_list[i]->hoop ->remove_me = true;
					ch_list[i]->crystal->remove_me = true;
				}
		}
}
void update(int useless)
{
		int timeElapsed = glutGet(GLUT_ELAPSED_TIME);
		
		if(life==0)
			gameover = true;
		if(!gameover)
		{
			for(unsigned int i = 0; i < giList.size(); i++)
			{
				giList[i]->update(timeElapsed);		
				
				if(giList[i]->getType() == SPACECRAFT)
				{
					giAircraft *aircraft = (giAircraft *)giList[i];

					
					if(chasecamera)
					{
						point3d *newPos = spherePoint(aircraft->position,10.0f,360 - aircraft->pitch,aircraft->heading -90);  
						mainCamera->movePosition(newPos);
						mainCamera->moveTarget(aircraft->position);
					}
					else{				
								thirdCameras[thirdCameraSelection]->moveTarget(aircraft->position);
								if(lastKeyProcess + 100 < timeElapsed)
								{
									if(Keyboard::DOWN || Keyboard::UP)
									{
											if(Keyboard::UP)
												spacecraft->tiltMaxSpeedAdd(0.2f);
											if(Keyboard::DOWN)
												spacecraft->tiltMaxSpeedAdd(-0.2f);
									}else
										spacecraft->desired_tiltSpeed = 0;
									if(Keyboard::LEFT || Keyboard::RIGHT)
									{
										if(Keyboard::LEFT)
											spacecraft->turnMaxSpeedAdd(0.2f);
										if(Keyboard::RIGHT)
											spacecraft->turnMaxSpeedAdd(-0.2f);
									}else
										spacecraft->desired_turnSpeed = 0;

									lastKeyProcess = timeElapsed;
								}
					}

						for(unsigned int j = 0; j < giList.size(); j++)
						{
							if(giList[j]->getType() == PLANET)
							{
								if(collision::collides(giList[j]->myShape, giList[i]->myShape))
								{
									damage(150);
								}
							}else if(giList[j]->getType() == PLANET)
							{
								if(collision::collides(giList[j]->myShape, giList[i]->myShape))
								{
									damage(80);
								}
							}else if(giList[j]->getType() == HOOP)
							{
								if(collision::collides(giList[j]->myShape, giList[i]->myShape))
								{
									damage(30);
									chRemove(giList[j]);
									generateHoops(1);
								}
							}else if(giList[j]->getType() == CRYSTAL)
							{
								if(collision::collides(giList[j]->myShape, giList[i]->myShape))
								{
									progress++;
									chRemove(giList[j]);	
									generateHoops(1);
								}
							}else if(giList[j]->getType() == SKYBOX)
							{
								if(collision::collides_sphere_sphere_edge(giList[i]->myShape, giList[j]->myShape))
								{
									Rotation *r = getAngles(new point3d(0,0,0),spacecraft->position);
									spacecraft->position = spherePoint(new point3d(0,0,0), 190.0f, r->pitch ,r->yaw +180);//need verification
							
								}
							}
						}
				}else if(giList[i]->getType() == POINTER)
				{
					point3d *newPos = spherePoint(spacecraft->position,5.0f,380 - spacecraft->pitch,spacecraft->heading -90);  
					((giPointer *)giList[i])->moveTo(newPos);
					((giPointer *)giList[i])->pointAt(ch_list[0]->hoop->position);
				}
			}

			//generate a new array, efficiently removing objects that we dont want to use anymore.
			vector<GameItem *> newgiList;
			for(unsigned int i = 0; i < giList.size(); i++)
			{
					if(!giList[i]->remove_me)
						newgiList.push_back(giList[i]);
			}
			//replace the gamelist array with this new one.
			giList = newgiList;

			//generate a new array, efficiently removing objects that we dont want to use anymore.
			vector<CrystalLink *> newchList;
			for(unsigned int i = 0; i < ch_list.size(); i++)
			{
					if(!ch_list[i]->hoop->remove_me)
						newchList.push_back(ch_list[i]);
			}
			float tmp_size = ch_list.size();
			//replace the gamelist array with this new one.
			ch_list = newchList;

					pushHoopSelection();
	}
	if(chasecamera)
	{
		mainCamera->update();
		glutWarpPointer(windowWidth/2,windowHeight/2);
	}
	else
		thirdCameras[thirdCameraSelection]->update();



	glutPostRedisplay();
	glutTimerFunc(1,update,1);
}
void resize(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
    glViewport(0, 0, w, h);
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

	mainCamera->changeWindowSize(w, h);
	thirdCameras[0]->changeWindowSize(w, h);
	thirdCameras[1]->changeWindowSize(w, h);
	thirdCameras[2]->changeWindowSize(w, h);
	thirdCameras[3]->changeWindowSize(w, h);

	//mainCamera->update();	
}
void generatePlanets(int count)
{		
		for(int i = 0; i < count; i++)
		{
			float rad = randFloat(1.8f, 3.5f);
			float dist = randFloat(10.0f + rad, (190.0f) - (rad));

			giList.push_back(new giPlanet(rad, dist, new point3d(randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f)), new point3d(0.0f, randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f))));	
		}
}
void generateHoops(int count)
{
	for(int i = 0; i < count; i++)
	{
		float progress_mod = (progress/3.0f) + 1.0f;
		if(progress_mod> 8.0f)
			progress_mod = 8.0f;
		float rad = randFloat(9.0f, 28.0f/progress_mod);
		float cs_radius = randFloat(0.1f * progress_mod, 3.0f);
		
		float angle_heading =  randFloat(0.0f, 360.0f);
		float angle_pitch =  randFloat(0.0f, 360.0f) - 180.0f;

		float dist = randFloat(10.0f + (rad+cs_radius), (190.0f) - (rad+cs_radius));

		point3d *loc = spherePoint(new point3d(0,0,0), dist, angle_pitch, angle_heading);
		GameItem *gi_tmp = new giHoop(loc, rad, cs_radius,  randFloat(0.0f, 360.0f),  randFloat(0.1f*progress_mod, 1.0f * progress_mod));
		GameItem *gi_tmp_cry = new giCrystal(loc);

		giList.push_back(gi_tmp);	
		giList.push_back(gi_tmp_cry);

		ch_list.push_back(new CrystalLink(gi_tmp_cry,gi_tmp));
	}
	 pushHoopSelection();
}
void pushHoopSelection()
{
	if(ch_list.size() > 0 && !((giHoop*)ch_list[0]->hoop)->selected)
	{
		((giHoop*)ch_list[0]->hoop)->selected = true;
	}
}