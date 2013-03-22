#ifndef DrawerSprite_h__
#define DrawerSprite_h__

#include "Drawer.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

namespace MA
{

class Entity;

class DrawerSprite : public Drawer
{
public:
    DrawerSprite(CL_GraphicContext &gc, CL_Sprite aSprite);

    void draw(const Entity &aEntity);

private:
    CL_GraphicContext &mGc;
    CL_Sprite mSprite;
};

}
#endif // DrawerSprite_h__
