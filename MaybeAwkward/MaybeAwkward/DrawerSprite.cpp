#include "DrawerSprite.h"

#include "Entity.h"
#include "GraphicWrapper.h"
#include "Camera.h"

using namespace MA;
#define INTEGRAL_SCROLLING

#include "Entity.h"

DrawerSprite::DrawerSprite(GraphicWrapper &gc, CL_Sprite aSprite):
    mGc(gc),
    mSprite(aSprite)
{
}

void DrawerSprite::draw(const Entity &aEntity)
{
    mSprite.set_angle(CL_Angle(aEntity.angle(), cl_radians));
#ifdef INTEGRAL_SCROLLING 
	mSprite.draw(mGc.cl(), (float)floor(aEntity.x()+0.5f - mGc.camera().pos()*(aEntity.cameraFactor())), (float)floor(aEntity.y()+0.5f));
#else
	mSprite.draw(mGc.cl(), aEntity.x() - mGc.camera().pos(), aEntity.y());
#endif
}
