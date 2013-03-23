#ifndef Entity_h__
#define Entity_h__

#include "Node.h"
#include "Visitor.h"
#include "Physics.h"

#include <assert.h>
#include <memory>
#include <stdio.h>

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

    const float x() const
    {
        return PhysicsSystem::get(mPhysics)->x();
        printf("get x: %f\n", PhysicsSystem::get(mPhysics)->x());
    }

    const float y() const
    {
        return PhysicsSystem::get(mPhysics)->y();
    }

    virtual void getVisited(Visitor &aVisitor)
    {
        aVisitor.visit(this);
    }

    void setPhysicsID(PhysicsID id) {
        assert(mPhysics.type == PHYSICS_INVALID || 
               id.type == PHYSICS_INVALID);
        mPhysics = id;
    }

    PhysicsID physicsID() const {
        return mPhysics;
    }

protected:
    std::shared_ptr<Controller> mController;
    std::shared_ptr<Drawer> mDrawer;
    PhysicsID mPhysics;
};

}

#endif // Entity_h__
