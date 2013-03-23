#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"

#include "constants.h"
#include "MoveMessage.h"
#include "AttackMessage.h"

#include <ClanLib/core.h>

using namespace MA;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mMessageBox(),
    mController(aController),
    mDrawer(aDrawer)
{
}

void Entity::update(float dt)
{
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
}

void Entity::draw()
{
    mDrawer->draw(*this);
}

void Entity::visit(AbstractMessage *aVisitedNode, const VisitInfo &info)
{
    //do nothing (could log it for functionnal error tracing)
    cl_log_event("warning", "Unhandled message.");
}

void Entity::visit(MoveMessage *aMessage, const VisitInfo &info)
{
    PhysicsSystem::applyForce(mPhysics, aMessage->X, aMessage->Y);
}

void Entity::visit(AttackMessage *aMessage, const VisitInfo &info)
{
    if(aMessage->attack)
    {
        CL_Console::write_line("Attack with angle : %1", aMessage->angle);
    }
        
}