#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"
#include "Physics.h"

#include "constants.h"
#include "MoveMessage.h"
#include "AttackMessage.h"
#include "SpeedMessage.h"
#include "AttackerNull.h"
#include "DeletionHandlerNull.h"
#include "AnimatorNull.h"

#include "World.h"
#include "GraphicWrapper.h"
#include "Camera.h"

#include <string>
#include <ClanLib/core.h>

#define DRAW_HITBOX

using namespace MA;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mMessageBox(),
    mController(aController),
    mDrawer(aDrawer),
    mAttacker(std::make_shared<AttackerNull>()),
    mDeletionHandler(std::make_shared<DeletionHandlerNull>()),
    mAnimator(std::make_shared<AnimatorNull>()),
    mChildEntities(),
    mMarkedForDeletion(false),
    mState(IDLE),
	mCameraFactor(1.0f)
{
}

Entity::~Entity()
{
    PhysicsSystem::removeEntity(*this);
}

bool Entity::update(float dt)
{
    Camera &worldCam = World::instance.getGraphicWrapper().camera();
    if (mMarkedForDeletion || 
        (pow(x()-worldCam.pos(), 2) > WIN_WIDTH_SQUARED) ||
        (pow(y(), 2) > WIN_HEIGHT_SQUARED))
    {
        return mDeletionHandler->deletion(*this);;
    }

    mController->update(*this, dt);

    mAnimator->animate(*this);

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
/*
    if (name() == "Nounours" && checkStateChange() != NO_CHANGE) {
        printf("State Change!\n");
    }
*/
    return false;
}

void Entity::draw()
{
    if(mChildEntities.size() == 0)
    {
        mDrawer->draw(*this);
#ifdef DRAW_HITBOX
        PhysicalObject *physic = getPhysics();
        CL_Draw::box(World::instance.getGraphicWrapper().cl(),
            CL_Rectf(physic->boundingRect()),
            CL_Colorf::bisque);
#endif
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

void Entity::visit(SpeedMessage *aMessage, const VisitInfo &info)
{
	PhysicsSystem::get(mPhysics)->setXVelocity(aMessage->Y*TOP_SPEED - aMessage->X*TOP_SPEED);
    if(aMessage->jump)
        PhysicsSystem::get(mPhysics)->setYVelocity(-500.f);
}

void Entity::visit(MoveMessage *aMessage, const VisitInfo &info)
{
	PhysicsSystem::applyForce(mPhysics, aMessage->X, aMessage->Y);
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

void Entity::visit(AnimationMessage *aMessage, const VisitInfo &info)
{
	
}


namespace MA
{

const char* animEnumToNounoursStr(AnimState state) {
    switch (state) {    
        case NO_CHANGE: return "";
        case IDLE: return "nounours_idle";
        case WALKING: return "nounours_walk";
        case JUMPING_UP: return "nounours_jump_up";
        case JUMPING_DOWN: return "nounours_jump_down";
    }
    return "";
}

}