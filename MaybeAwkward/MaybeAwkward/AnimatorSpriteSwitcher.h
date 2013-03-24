#ifndef AnimatorSpriteSwitcher_h__
#define AnimatorSpriteSwitcher_h__

#include <memory>

#include <string>
#include "Animator.h"

namespace MA
{
    class Animator;
    class SpriteComponent;

class AnimatorSpriteSwitcher : public Animator
{
public:
    void animate(Entity &aEntity);
    AnimatorSpriteSwitcher(const std::string &aRessourcesfile);
private:
    std::unique_ptr<SpriteComponent> mSpriteComponent;
};
}

#endif // AnimatorSpriteSwitcher_h__
