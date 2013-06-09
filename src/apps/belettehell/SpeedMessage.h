#ifndef SpeedMessage_h__
#define SpeedMessage_h__

#include "MessageParent.h"

namespace MA
{

class SpeedMessage : public MessageParent<SpeedMessage>
{
public:
    SpeedMessage(float X, float Y, bool jump):
        X(X),
        Y(Y),
        jump(jump)
    {}

        //Public attributes
    float X, Y;
    bool jump;
};
}
#endif // MoveMessage_h__
