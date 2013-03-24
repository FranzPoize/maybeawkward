#ifndef AttackerBullet_h__
#define AttackerBullet_h__

#define  BULLET_POOL_SIZE 200

#include "Attacker.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include <vector>

namespace MA
{
class AttackerBullet : public Attacker
{
    void attack(const AttackMessage *aAttackMessage, const Entity &aEntity);
};

class BulletPool
{
public:
    BulletPool(std::vector<std::shared_ptr<Entity> >::size_type aInitialSize=BULLET_POOL_SIZE);
    std::shared_ptr<Entity> getNextBullet();

private:
    std::vector<std::shared_ptr<Entity> > mPoolContainer;
    std::vector<std::shared_ptr<Entity> >::iterator mNextBullet;

    static CL_Sprite gBulletSprite;
};
}
#endif // AttackerBullet_h__
