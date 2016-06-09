#include "shared/gltools.h"


#include "globals.h"
#include "geometry.h"
#include "shape.h"
#include "collision.h"
#include "camera.h"
#include "ObjLoader.h"
#include "GameItem.h"
#include "textures.h"
#include "HUD.h"
#include "CrystalLink.h"
#include "Keyboard.h"

#include "giAircraft.h"
#include "giSkybox.h"
#include "giSun.h"
#include "giHoop.h"
#include "giCrystal.h"
#include "giPointer.h"
#include "giPlanet.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <vector>

#include <cmath>
using namespace std;

GLfloat  specLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat  defuseLight[] = { 0.8f,  0.8f, 0.8f,  1.0f };
GLfloat  ambiantLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

camera *mainCamera;
int windowWidth = 1066, windowHeight = 800;

vector<GameItem *> giList;
vector<CrystalLink *> ch_list;

bool chasecamera = true;
int thirdCameraSelection = 2;
camera *thirdCameras[4];

int life = 100;
int hull = 100;
int score = 0;
int progress = 0;
int lastKeyProcess = 0;
bool gameover = false;

void init(void);
void render(void);
void resize(int width, int height);
void update(int unknown);
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void mouseMove(int x, int y);
void renderHUD();
void generateHoops(int count);
void pushHoopSelection();
void chRemove(GameItem *item);
void generatePlanets(int count);
void damage(int damage_amt);
void keyDownSpec(int key, int x, int y);