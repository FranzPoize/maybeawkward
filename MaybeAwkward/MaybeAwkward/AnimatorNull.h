#ifndef AnimatorNull_h__
#define AnimatorNull_h__

#include "Animator.h"

namespace MA
{
class AnimatorNull : public Animator
{
    void animate(Entity &aEntity)
    {
        return;
    }
};
}
#endif // AnimatorNull_h__
