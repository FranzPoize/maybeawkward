#ifndef SpriteComponent_h__
#define SpriteComponent_h__

#include <string>
#include <map>

#include "DrawerSprite.h"

namespace MA
{
    class Entity;
    class SpriteComponent
    {
    public:
        SpriteComponent(GraphicWrapper &gc, std::string resourceFileName);
        void addDrawer(std::string drawerName, std::shared_ptr<MA::DrawerSprite> drawer);
        std::shared_ptr<MA::DrawerSprite> getDrawer(std::string drawerName);

    protected:
        std::map<std::string, std::shared_ptr<MA::DrawerSprite>> drawersList;

    };

}
#endif // XBoxController_h__