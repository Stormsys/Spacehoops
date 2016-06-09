#ifndef TEXTURES_H
#define TEXTURES_H
#include "shared/gltools.h"
#include "globals.h"

class Textures
{
public:
	static void LoadAll();
	static void Use(int which);
	static void Done();
private:

};
#endif