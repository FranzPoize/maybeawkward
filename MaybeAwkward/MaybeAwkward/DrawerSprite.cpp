#include "DrawerSprite.h"

#include "Entity.h"
#include "GraphicWrapper.h"
#include "Camera.h"

using namespace MA;

DrawerSprite::DrawerSprite(GraphicWrapper &gc, CL_Sprite aSprite):
    mGc(gc),
    mSprite(aSprite)
{
}

void DrawerSprite::draw(const Entity &aEntity)
{
    mSprite.set_angle(CL_Angle(aEntity.angle(), cl_radians));
	mSprite.draw(mGc.cl(), (float)floor(aEntity.x()+0.5f - mGc.camera().pos()), (float)aEntity.y());
}
