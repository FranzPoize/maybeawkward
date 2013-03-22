#ifndef Controller_h__
#define Controller_h__

namespace AB
{

class Entity;

class Controller
{
public:
    virtual void update(Entity &aEntity, float dt) =0;
};

}
#endif // Controller_h__
