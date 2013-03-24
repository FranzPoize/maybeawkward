#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"

#include "constants.h"
#include "MoveMessage.h"
#include "AttackMessage.h"
#include "AttackerNull.h"
#include "DeletionHandlerNull.h"

#include "World.h"
#include "GraphicWrapper.h"
#include "Camera.h"

#include <ClanLib/core.h>

using namespace MA;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mMessageBox(),
    mController(aController),
    mDrawer(aDrawer),
    mAttacker(std::make_shared<AttackerNull>()),
    mDeletionHandler(std::make_shared<DeletionHandlerNull>()),
    mChildEntities()
{
}

bool Entity::update(float dt)
{
    Camera &worldCam = World::instance.getGraphicWrapper().camera();
    if( (pow(x()-worldCam.pos(), 2) > WIN_WIDTH_SQUARED) || (pow(y(), 2) > WIN_HEIGHT_SQUARED))
    {
        mDeletionHandler->deletion(*this);
        return true;
    }

    mController->update(*this, dt);

    VisitInfo info;
    info.dt = dt;
    for(MessageBoxIterator messageIt = mMessageBox.begin();
        messageIt != mMessageBox.end();
        ++messageIt)
    {
        (*messageIt)->getVisited(*this, info);
    }

    mMessageBox.clear();

    for(ChildIterator childIt = mChildEntities.begin();
        childIt != mChildEntities.end();
        ++childIt)
    {
        childIt->second->update(dt);
    }

    return false;
}

void Entity::draw()
{
    if(mChildEntities.size() == 0)
    {
        mDrawer->draw(*this);
    }
    else
    {
        bool crossedZeroOrder = false;
        for(ChildIterator childIt = mChildEntities.begin();
            childIt != mChildEntities.end();
            ++childIt)
        {
            if ( (!crossedZeroOrder) && (childIt->first >= 0) )
            {
                mDrawer->draw(*this);
                crossedZeroOrder = true;
            }
            childIt->second->translate(x(), y());
            childIt->second->draw();
        }
    }
}

void Entity::visit(AbstractMessage *aVisitedNode, const VisitInfo &info)
{
    //do nothing (could log it for functionnal error tracing)
    cl_log_event("warning", "Unhandled message.");
}

void Entity::visit(MoveMessage *aMessage, const VisitInfo &info)
{
    PhysicsSystem::applyForce(mPhysics, aMessage->Y-aMessage->X, 0.f);
    if(aMessage->jump)
        PhysicsSystem::get(mPhysics)->setYVelocity(-500.f);
}

void Entity::visit(AttackMessage *aMessage, const VisitInfo &info)
{
    if(aMessage->attack)
    {
        mAttacker->attack(aMessage, *this);
    }
    PhysicsSystem::get(mPhysics)->setAngle(aMessage->angle);
}