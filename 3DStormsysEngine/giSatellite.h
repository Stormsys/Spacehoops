#include "GameItem.h"
#include "ObjLoader.h"

class giSatellite : public GameItem
{
public:
	giSatellite();	
	void render();
	void update(int time);	
	GameItemType getType();

private:
	ObjModel *myModel;
	int last_elapsed;
};