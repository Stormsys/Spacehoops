#ifndef GLOBALS_H
#define GLOBALS_H
#include "geometry.h"
#include "shared/gltools.h"

#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265

#define ENGINE_DEBUG true


enum ShapeType { AP_BOX/*Axis-Parralel Box*/, SPHERE, UR_TORUS };

enum GameItemType { NA, SPACECRAFT, PLANET, SKYBOX, SATELLITE, HOOP, CRYSTAL,POINTER};

#define TEXTURE_COUNT 14
#define TEXTURE_SKYBOX 0
#define TEXTURE_SUN 1
#define TEXTURE_HOOPS 2
#define TEXTURE_HOOPS_S 3
#define TEXTURE_PLANET_EARTH 4
#define TEXTURE_PLANET_MARS 5
#define TEXTURE_PLANET_JUPITER 6
#define TEXTURE_PLANET_VENUS 7
#define TEXTURE_MINIMAP 8
#define TEXTURE_MINIMAP_SPACECRAFT 9
#define TEXTURE_HUD_LIFEBAR 10
#define TEXTURE_HUD_SHEILD 11
#define TEXTURE_HUD_HEALTH 12
#define TEXTURE_SCORE_ORB 13

#define TEXTURE_PLANET_START 4
#define TEXTURE_PLANET_END 7

float randFloat(float a, float b);
float degToRad(float deg);

point3d *spherePoint(point3d *centre, float radius, float pitch, float heading);
float pointDistance(point3d *p1, point3d *p2);
float radToDeg(float rad);
void drawTorus(float r, float R, float nsides, float rings);

Rotation *getAngles(point3d *p1, point3d* p2);
int randInt(int min, int max);
#endif