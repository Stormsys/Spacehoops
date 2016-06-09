#ifndef CRYSTAL_LINK_H
#define CRYSTAL_LINK_H
#include "GameItem.h"
class CrystalLink	
{
public:
	GameItem *crystal;
	GameItem *hoop;

	CrystalLink(GameItem *crystal, GameItem *hoop);
};

#endif