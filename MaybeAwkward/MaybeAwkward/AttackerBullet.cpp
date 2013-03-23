#include "AttackerBullet.h"

#include "AttackMessage.h"
#include "World.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "Physics.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <memory>
#include <list>

using namespace MA;

/// \todo : move out static declarations
std::shared_ptr<Entity> generateBullet(CL_Pointf &aOrigin, CL_Pointf &aDirection)
{
    CL_SpriteDescription bulletDescription;
    bulletDescription.add_frame(ASSET_PATH+"design_export/nounours_marche/nounours_marche_00.png");

    CL_Sprite bulletSprite(World::instance.getGraphicWrapper().cl(), bulletDescription);
    bulletSprite.set_alignment(origin_bottom_left);
    std::shared_ptr<Drawer> bulletDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), bulletSprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
    std::shared_ptr<Entity> bullet = std::make_shared<Entity>(controllerNull, bulletDrawer);

    PhysicsMaterial bulletMaterial(EPSILON, EPSILON, 10000.f, 13, 13);
    PhysicsSystem::addEntity(*bullet, PHYSICS_BOX);
    PhysicsSystem::setPosition(bullet->physicsID(), aOrigin.x,  aOrigin.y);

    PhysicsSystem::get(bullet->physicsID())->setXVelocity(aDirection.x*BULLET_SPEED);
    PhysicsSystem::get(bullet->physicsID())->setYVelocity(aDirection.y*BULLET_SPEED);

    return bullet;
}

void AttackerBullet::attack(const AttackMessage *aAttackMessage, const Entity &aEntity)
{
    CL_Pointf dir(1.f, 0.f);
    dir.rotate(CL_Vec2<float>(0.f, 0.f), CL_Angle::from_radians(aAttackMessage->angle));

    World::instance.everybodyList().push_back(generateBullet(CL_Pointf(aEntity.x(), aEntity.y()), dir));

}
