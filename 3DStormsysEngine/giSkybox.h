#include "GameItem.h"


#include "textures.h"

class giSkybox : public GameItem
{
public:
	giSkybox();	
	void render();
	void update(int time);	
	GameItemType getType();

private:
	int last_rot_elapsed, last_change_elapsed;
	float rotx, roty, rotz;
	float changex, changey, changez;

};