#ifndef AttackMessage_h__
#define AttackMessage_h__

#include "MessageParent.h"
namespace MA
{
class AttackMessage : public MessageParent<AttackMessage>
{
public:
    AttackMessage(bool attack, float angle):
        attack(attack),
        angle(angle)
      {
      }

public:
    bool attack;
    float angle;
};
}
#endif // AttackMessage_h__
