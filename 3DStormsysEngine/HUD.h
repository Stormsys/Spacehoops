#ifndef HUD_H
#define HUD_H

#include "GameItem.h"
#include "CrystalLink.h"
#include "giAircraft.h"

class HUD
{
public:
	static void drawRadar(giAircraft * aircraft, vector<CrystalLink *> crystals);
	static void drawHUD(giAircraft * aircraft, float windowWidth, float windowHeight, float sheild, float life);
private:
	static void drawMMSpaceship(giAircraft * aircraft);
	static void plotMMHoops(vector<CrystalLink *> crystals);
	static void drawRadarBack();
	
	static void drawArc(float windowWidth, float windowHeight);
	static void drawLevelIndicators(giAircraft *aircraft, float windowWidth, float windowHeight);
	static void drawStaticIndicators(giAircraft *aircraft, float windowWidth, float windowHeight);
	static void drawLifeBar(float windowWidth, float windowHeight, float sheild, float life);
	static void drawSheild();
	static void drawHealth();
	static void animateSheildHealth(float hull, float life);
};




#endif