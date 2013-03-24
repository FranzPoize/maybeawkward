#ifndef AttackerNull_h__
#define AttackerNull_h__

#include "Attacker.h"

namespace MA
{
class AttackerNull : public Attacker
{
    void attack(const AttackMessage *aAttackMessage, const Entity &aEntity)
    {
    }
};
}
#endif // AttackerNull_h__
