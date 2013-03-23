#ifndef Entity_h__
#define Entity_h__

#include "Node.h"
#include "Visitor.h"

#include <memory>

namespace MA
{

class Controller;
class Drawer;

class Entity : public Node
{
public:
    //Entity(std::shared_ptr<Controller> aController);
    Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer);


    void update(float dt);
    void draw();

    void move(float dt, float aXInput, bool aJump);

    const float &x() const
    {
        return mXpos;
    }

    const float &y() const
    {
        return mYpos;
    }

    virtual void getVisited(Visitor &aVisitor)
    {
        aVisitor.visit(this);
    }


protected:
    std::shared_ptr<Controller> mController;
    std::shared_ptr<Drawer> mDrawer;

    float mXpos;
    float mYpos;

};

}

#endif // Entity_h__
