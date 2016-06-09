#ifndef GAMEITEM_H
#define GAMEITEM_H
#include "shared/gltools.h"
#include "globals.h"
#include "geometry.h"
#include "shape.h"
#include <iostream>
#include <string>

using namespace std;

class GameItem
{
public:
	virtual void update(int timeElapsed);
	virtual void render();	
	virtual void die();	
	virtual GameItemType getType();
	virtual void keyboard(unsigned char key);
	point3d *position;


	bool remove_me, gravityAffects;
	shape *myShape;	
private:
	
};

#endif