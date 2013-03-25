#include "AttackerBullet.h"

#include "AttackMessage.h"
#include "World.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "Physics.h"
#include "Entity.h"

#include <memory>
#include <list>

using namespace MA;

/// \todo : move out static declarations

CL_Pointf GUN_HOLE(105.f, -96.f);

std::shared_ptr<Entity> generateBullet(CL_Sprite &aSprite)
{
    std::shared_ptr<Drawer> bulletDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), aSprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
    std::shared_ptr<Entity> bullet = std::make_shared<Entity>(controllerNull, bulletDrawer);
    bullet->families().push_back(FRIEND_BULLET);

    PhysicsMaterial bulletMaterial(EPSILON, EPSILON, 10000.f, 13, 13);
    PhysicsSystem::addEntity(*bullet, PHYSICS_BOX, &bulletMaterial);

    return bullet;
}

void fireBullet(std::shared_ptr<Entity> aBullet, CL_Pointf &aOrigin, CL_Pointf &aDirection, const Entity &aEntity)
{
    PhysicsSystem::setPosition(aBullet->physicsID(), aOrigin.x,  aOrigin.y);

	PhysicsSystem::get(aBullet->physicsID())->setXVelocity((aDirection.x+rand()%2/10.f)*BULLET_SPEED+World::instance.pibiRef->getPhysics()->getXVelocity());
    PhysicsSystem::get(aBullet->physicsID())->setYVelocity((aDirection.y+rand()%2/10.f)*BULLET_SPEED);
}

void AttackerBullet::attack(const AttackMessage *aAttackMessage, const Entity &aEntity)
{
    static int DROP = 1;
    static int cnt = 0;

    if(cnt%DROP)
    {
        return;
    }
    CL_Pointf dir(1.f, 0.f), origin=mOrigin;
    dir.rotate(CL_Vec2<float>(0.f, 0.f), CL_Angle::from_radians(aAttackMessage->angle));
 
    //origin.rotate(CL_Vec2<float>(0.f, 0.f), CL_Angle::from_radians(aAttackMessage->angle));
    origin += CL_Pointf(aEntity.x(), aEntity.y());
    origin += dir*95;

    std::shared_ptr<Entity> bullet(World::instance.gBulletPool->getNextBullet());
    fireBullet(bullet, origin, dir, aEntity);
    World::instance.everybodyList().push_back(bullet);
}

BulletPool::BulletPool(std::vector<std::shared_ptr<Entity> >::size_type aInitialSize)
{
    CL_SpriteDescription bulletDescription;
    bulletDescription.add_frame(ASSET_PATH+"design_export/tir_bleu.png");

    CL_Sprite bulletSprite = CL_Sprite(World::instance.getGraphicWrapper().cl(), bulletDescription);
    bulletSprite.set_alignment(origin_bottom_left);
    
    for (std::vector<std::shared_ptr<Entity> >::size_type bullId=0;
        bullId != aInitialSize;
        ++bullId)
    {
        mPoolContainer.push_back(generateBullet(bulletSprite));
    }

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
