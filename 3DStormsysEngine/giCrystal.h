#include "GameItem.h"

#include "textures.h"
#include "ObjLoader.h"

class giCrystal : public GameItem
{
public:
	giCrystal(point3d *loc);
	void render();
	void update(int time);	
	GameItemType getType();

private:
	ObjModel *myModel;
};