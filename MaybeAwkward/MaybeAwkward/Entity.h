#ifndef Entity_h__
#define Entity_h__

#include "Physics.h"
#include "MessageVisitor.h"
#include "MessageReceiver.h"
#include "AbstractMessage.h"

#include <assert.h>
#include <memory>
#include <stdio.h>
#include <deque>

namespace MA
{

class Controller;
class Drawer;
class AbstractMessage;
class MoveMessage;

class Entity : public MessageVisitor, public MessageReceiver
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

    void receiveMessage(std::shared_ptr<AbstractMessage> aInputMessage)
    {
        mMessageBox.push_back(aInputMessage);
    }

    void setPhysicsID(PhysicsID id) {
        assert(mPhysics.type == PHYSICS_INVALID || 
               id.type == PHYSICS_INVALID);
        mPhysics = id;
    }

    PhysicsID physicsID() const {
        return mPhysics;
    }

    // To be overloaded in derived class (will cause name hiding problems...)
    void visit(AbstractMessage *aVisitedNode, const VisitInfo &info);

    void visit(MoveMessage *aMessage, const VisitInfo &info);

    typedef std::deque<std::shared_ptr<AbstractMessage> > MessageBoxType;
    typedef MessageBoxType::iterator MessageBoxIterator;

    MessageBoxType mMessageBox;
    std::shared_ptr<Controller> mController;
    std::shared_ptr<Drawer> mDrawer;
    PhysicsID mPhysics;
};

}

#endif // Entity_h__
