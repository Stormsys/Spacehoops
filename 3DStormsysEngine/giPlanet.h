#include "GameItem.h"


#include "textures.h"

class giPlanet : public GameItem
{
public:
	giPlanet(float rad_planet, float rad_dist, point3d * rot, point3d *orbit);
	void render();
	void update(int time);	
	GameItemType getType();

private:
	int last_rot_elapsed;
	int planet;
	float rotx, roty, rotz;
	float orbitx, orbity, orbitz;
	float rotx_speed, roty_speed, rotz_speed;
	float orb_x_speed, orb_y_speed, orb_z_speed;
	float orbit_radius;
	float planet_radius;
};