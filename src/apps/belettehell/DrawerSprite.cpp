#include "DrawerSprite.h"

#include "Entity.h"
#include "GraphicWrapper.h"
#include "Camera.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/application.h>
#include <sstream>

using namespace MA;
#define INTEGRAL_SCROLLING

//#define DRAW_HITBOX

#include "Entity.h"

DrawerSprite::DrawerSprite(GraphicWrapper &gc, clan::Sprite aSprite):
    mGc(gc),
    mSprite(aSprite)
{
}

void DrawerSprite::draw(const Entity &aEntity)
{
    mSprite.set_angle(clan::Angle(aEntity.angle(), clan::radians));
    mSprite.update();
#ifdef INTEGRAL_SCROLLING 
	mSprite.draw(mGc.cl(), (float)floor(aEntity.x()+0.5f - mGc.camera().pos()*(aEntity.cameraFactor())), (float)floor(aEntity.y()+0.5f));
#else
	mSprite.draw(mGc.cl(), aEntity.x() - mGc.camera().pos(), aEntity.y());
#endif

#ifdef DRAW_HITBOX
	clan::Vec4d offsetBox = clan::Vec4d(-mGc.camera().pos()*(aEntity.cameraFactor()),
									0.f,
									-mGc.camera().pos()*(aEntity.cameraFactor()),
									0.f)
						+ aEntity.getBoundingBox();

    clan::Draw::box(mGc.cl(),
        clan::Rectf(offsetBox.x,offsetBox.y,offsetBox.z,offsetBox.w),
        clan::Colorf::bisque);

	//std::ostringstream oss;
	//oss << "Entity : " << aEntity.x() << "," << aEntity.y() 
	//	<< ". Bounding Box : " << clan::Vec4d(aEntity.getBoundingBox()).x << "," << clan::Vec4d(aEntity.getBoundingBox()).w << std::endl;
	//clan::Console::write_line(oss.str());
#endif
}
