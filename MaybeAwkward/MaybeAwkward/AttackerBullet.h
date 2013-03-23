#ifndef AttackerBullet_h__
#define AttackerBullet_h__

#include "Attacker.h"
namespace MA
{
class AttackerBullet : public Attacker
{
    void attack(const AttackMessage *aAttackMessage, const Entity &aEntity);
};
}
#endif // AttackerBullet_h__
