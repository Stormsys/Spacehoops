#ifndef GI_AIRCRAFT_H
#define GI_AIRCRAFT_H
#include "GameItem.h"
#include "ObjLoader.h"

class giAircraft : public GameItem
{
public:
	giAircraft();	
	void render();	
	void update(int timeElapsed);
	GameItemType getType();
	void turnMaxSpeedAdd(float num);
	void tiltMaxSpeedAdd(float num);
	
	float pitch;
	float heading;
	float roll;
	float desired_turnSpeed,desired_tiltSpeed, actual_turnSpeed;
private:

	ObjModel *myModel;
	float headingDest, pitchDest;
	float actual_tiltSpeed;
	int last_orient_update, lightAngle;
};
#endif