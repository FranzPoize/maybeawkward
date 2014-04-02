#ifndef AttackerBullet_h__
#define AttackerBullet_h__

#define  BULLET_POOL_SIZE 200

#include "Attacker.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include <vector>

namespace MA
{
class World;

class AttackerBullet : public Attacker
{
public:
    AttackerBullet(clan::Pointf aRotationOrigin) :
        mOrigin(aRotationOrigin)
    {

    }
    void attack(const AttackMessage *aAttackMessage, const Entity &aEntity);
private:
    clan::Pointf mOrigin;
};

class BulletPool
{
public:
    std::shared_ptr<Entity> getNextBullet();

private:
    BulletPool(std::vector<std::shared_ptr<Entity> >::size_type aInitialSize=BULLET_POOL_SIZE);
    friend class World;
private:
    std::vector<std::shared_ptr<Entity> > mPoolContainer;
    std::vector<std::shared_ptr<Entity> >::iterator mNextBullet;

    static clan::Sprite gBulletSprite;
};
}
#endif // AttackerBullet_h__
