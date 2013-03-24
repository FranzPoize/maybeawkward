#ifndef Attacker_h__
#define Attacker_h__

namespace MA
{

class AttackMessage;
class Entity;

class Attacker
{
public:
   virtual void attack(const AttackMessage *aAttackMessage, const Entity &aEntity) =0;
};
}
#endif // Attacker_h__
