#include "AttackerBullet.h"

#include "AttackMessage.h"
#include "World.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "Physics.h"
#include "Entity.h"
#include "constants.h"

#include <memory>
#include <sstream>
#include <list>

using namespace MA;

/// \todo : move out static declarations

clan::Pointf GUN_HOLE(105.f, -96.f);

std::shared_ptr<Entity> generateBullet(clan::Sprite &aSprite)
{
    std::shared_ptr<Drawer> bulletDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), aSprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
    std::shared_ptr<Entity> bullet = std::make_shared<Entity>(controllerNull, bulletDrawer);
    bullet->families().push_back(FRIEND_BULLET);

    PhysicsMaterial bulletMaterial(EPSILON, EPSILON, 10000.f, 24., 24.);
    PhysicsSystem::addEntity(*bullet, PHYSICS_BOX, &bulletMaterial);

    return bullet;
}

void fireBullet(std::shared_ptr<Entity> aBullet, clan::Pointf &aOrigin, clan::Pointf &aDirection, const Entity &aEntity)
{
	aBullet->setPosition(aOrigin.x,  aOrigin.y);

    /// \todo : decouple this component from PiBi (that is exactly why you should not have globals...)
	aBullet->getPhysicalObject()->setXVelocity(
		(aDirection.x) * BULLET_SPEED + World::instance.pibiRef->getPhysicalObject()->getXVelocity());
    aBullet->getPhysicalObject()->setYVelocity(
		(aDirection.y) * BULLET_SPEED);
}

void AttackerBullet::attack(const AttackMessage *aAttackMessage, const Entity &aEntity)
{
    static int DROP = 1;
    static int cnt = 0;

    if(++cnt%DROP)
    {
        return;
    }
    clan::Pointf dir(1.f, 0.f), origin=mOrigin;
    dir.rotate(clan::Vec2<float>(0.f, 0.f), clan::Angle::from_radians(aAttackMessage->angle));
 
    //origin.rotate(clan::Vec2<float>(0.f, 0.f), clan::Angle::from_radians(aAttackMessage->angle));
    origin += clan::Pointf(aEntity.x(), aEntity.y());
    origin += dir*95;

    std::shared_ptr<Entity> bullet(World::instance.gBulletPool->getNextBullet());
    fireBullet(bullet, origin, dir, aEntity);
	if(!bullet->getLive())
	{
		World::instance.everybodyList().push_back(bullet);
		bullet->setLive(true);
	}

	cnt = 0;
}

BulletPool::BulletPool(std::vector<std::shared_ptr<Entity> >::size_type aInitialSize)
{
    clan::SpriteDescription bulletDescription;
    bulletDescription.add_frame(ASSET_PATH+"design_export/tir_bleu.png");

    clan::Sprite bulletSprite = clan::Sprite(World::instance.getGraphicWrapper().cl(), bulletDescription);
    bulletSprite.set_alignment(ORIGIN);
    
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
