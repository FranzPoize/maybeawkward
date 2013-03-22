#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"

#include "constants.h"
#include <ClanLib/core.h>

using namespace MA;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mController(aController),
    mDrawer(aDrawer),
    mXpos(0.f),
    mYpos(0.f)
{
}

void Entity::update(float dt)
{
    mController->update(*this, dt);
}

void Entity::draw()
{
    mDrawer->draw(*this);
}

void Entity::move(float dt, float aXInput, bool aJump)
{
    float mv = aXInput*TOP_SPEED*dt;
    mXpos += mv;
    if(mXpos<0.)
    {
        mXpos = 0.;
    }
}