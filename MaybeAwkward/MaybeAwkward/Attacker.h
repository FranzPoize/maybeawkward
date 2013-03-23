#ifndef Attacker_h__
#define Attacker_h__

namespace MA
{

class AttackMessage;

class Attacker
{
public:
   virtual void attack(const AttackMessage &aAttackMessage) =0;
};
}
#endif // Attacker_h__
