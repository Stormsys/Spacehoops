#include "GameItem.h"

#include "textures.h"

class giHoop : public GameItem
{
public:
	giHoop(point3d *loc, float r, float cs_r, float ry, float rotation_speed);
	void render();
	void update(int time);	
	GameItemType getType();

	bool selected;
private:
	int last_rot_elapsed;
	float roty, radius, cs_radius, rot_speed, thick, wide;
};