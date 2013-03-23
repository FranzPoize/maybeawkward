#ifndef DrawerSprite_h__
#define DrawerSprite_h__

#include "Drawer.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <memory>

namespace MA
{

class Entity;
class GraphicWrapper;

class DrawerSprite : public Drawer
{
public:
    DrawerSprite(GraphicWrapper &gc, CL_Sprite aSprite);

    void draw(const Entity &aEntity);

private:
    GraphicWrapper &mGc;
    CL_Sprite mSprite;
};

}
#endif // DrawerSprite_h__
