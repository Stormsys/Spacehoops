#ifndef GI_PIONTER_H
#define GI_PIONTER_H
#include "GameItem.h"

class giPointer : public GameItem
{
public:
	giPointer(point3d*pos, point3d*pointat);	
	void render();	
	void update(int timeElapsed);
	GameItemType getType();
	void pointAt(point3d*pointat);
	void moveTo(point3d*move);
private:
	point3d *_pointAt;
	float pitch, yaw;
};
#endif