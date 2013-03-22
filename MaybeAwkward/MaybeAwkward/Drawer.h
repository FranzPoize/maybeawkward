#ifndef Drawer_h__
#define Drawer_h__

namespace AB
{

class Entity;

class Drawer
{
public:
    virtual void draw(const Entity &aEntity) =0;

};

}
#endif // Drawer_h__
