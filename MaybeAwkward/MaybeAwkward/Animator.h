#ifndef Animator_h__
#define Animator_h__

namespace MA
{
class Entity;

class Animator
{
public:
    virtual void animate(Entity &aEntity) =0;
};
}
#endif // Animator_h__
