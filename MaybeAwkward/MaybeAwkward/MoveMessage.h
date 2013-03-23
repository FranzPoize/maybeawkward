#ifndef MoveMessage_h__
#define MoveMessage_h__

#include "MessageParent.h"

namespace MA
{

class MoveMessage : public MessageParent<MoveMessage>
{
public:
    MoveMessage(float X, float Y, bool jump):
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
