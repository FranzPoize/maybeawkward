#ifndef AnimationMessage_h__
#define AnimationMessage_h__

#include "MessageParent.h"
#include <string>

namespace MA
{

class AnimationMessage : public MessageParent<AnimationMessage>
{
public:
    AnimationMessage(string aAnimationName):
	  mAnimationName(aAnimationName)
    {}

        //Public attributes
    string mAnimationName;
};
}
#endif // MoveMessage_h__
