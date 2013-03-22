#include "DrawerSprite.h"

#include "Entity.h"

using namespace MA;

DrawerSprite::DrawerSprite(CL_GraphicContext &gc, CL_Sprite aSprite):
    mGc(gc),
    mSprite(aSprite)
{

}

void DrawerSprite::draw(const Entity &aEntity)
{
    mSprite.draw(mGc, floor(aEntity.x()+0.5f), aEntity.y());
}