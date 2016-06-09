#include "GameItem.h"

void GameItem::update(int timeElapsed)
{
}
void GameItem::render()
{
}
void GameItem::die()
{
	remove_me=true;
}
GameItemType GameItem::getType()
{
	return NA;
}
void GameItem::keyboard(unsigned char key)
{
}
