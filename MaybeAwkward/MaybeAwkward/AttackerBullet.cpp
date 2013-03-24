#include "AttackerBullet.h"

#include "AttackMessage.h"
#include "World.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "Physics.h"

#include <memory>
#include <list>

using namespace MA;

/// \todo : move out static declarations
CL_Sprite BulletPool::gBulletSprite;
BulletPool gBulletPool();

CL_Pointf GUN_HOLE(105.f, -96.f);

std::shared_ptr<Entity> generateBullet(CL_Sprite &aSprite)
{
    std::shared_ptr<Drawer> bulletDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), aSprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
    std::shared_ptr<Entity> bullet = std::make_shared<Entity>(controllerNull, bulletDrawer);

    PhysicsMaterial bulletMaterial(EPSILON, EPSILON, 10000.f, 13, 13);
    PhysicsSystem::addEntity(*bullet, PHYSICS_BOX);

    return bullet;
}

void fireBullet(std::shared_ptr<Entity> aBullet, CL_Pointf &aOrigin, CL_Pointf &aDirection)
{
    PhysicsSystem::setPosition(aBullet->physicsID(), aOrigin.x,  aOrigin.y);

    PhysicsSystem::get(aBullet->physicsID())->setXVelocity(aDirection.x*BULLET_SPEED);
    PhysicsSystem::get(aBullet->physicsID())->setYVelocity(aDirection.y*BULLET_SPEED);
}

void AttackerBullet::attack(const AttackMessage *aAttackMessage, const Entity &aEntity)
{
    CL_Pointf dir(1.f, 0.f), origin(25.f, -52.f);
    dir.rotate(CL_Vec2<float>(0.f, 0.f), CL_Angle::from_radians(aAttackMessage->angle));
 
    //origin.rotate(CL_Vec2<float>(0.f, 0.f), CL_Angle::from_radians(aAttackMessage->angle));
    origin += CL_Pointf(aEntity.x(), aEntity.y());
    origin += dir*75;

    

    
    std::shared_ptr<Entity> bullet(BulletPool().getNextBullet());
    fireBullet(bullet, origin, dir);
    World::instance.everybodyList().push_back(bullet);
}

BulletPool::BulletPool(std::vector<std::shared_ptr<Entity> >::size_type aInitialSize)
{
    CL_SpriteDescription bulletDescription;
    bulletDescription.add_frame(ASSET_PATH+"design_export/tir_bleu.png");

    BulletPool::gBulletSprite = CL_Sprite(World::instance.getGraphicWrapper().cl(), bulletDescription);
    gBulletSprite.set_alignment(origin_bottom_left);
    
    mPoolContainer.assign(aInitialSize, generateBullet(gBulletSprite));
    mNextBullet=mPoolContainer.begin();
}
std::shared_ptr<Entity> BulletPool::getNextBullet()
{
    //Start at bullet[1], we don't care
    ++mNextBullet;
    if(mNextBullet==mPoolContainer.end())
    {
        mNextBullet = mPoolContainer.begin();
    }
    return *mNextBullet;
}