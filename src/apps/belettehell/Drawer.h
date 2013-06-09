#ifndef Drawer_h__
#define Drawer_h__

#include <memory>

namespace MA
{

class Entity;
class GraphicWrapper;

class Drawer
{
public:
    virtual void draw(const Entity &aEntity) =0;
};

}
#endif // Drawer_h__
