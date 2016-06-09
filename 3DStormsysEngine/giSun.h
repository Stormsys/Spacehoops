#include "GameItem.h"


#include "textures.h"

class giSun : public GameItem
{
public:
	giSun();	
	void render();
	void update(int time);	
	GameItemType getType();

private:
	int last_rot_elapsed;
	float rotx, roty, rotz;
};