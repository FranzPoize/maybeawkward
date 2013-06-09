#ifndef AnimatorSpriteSwitcher_h__
#define AnimatorSpriteSwitcher_h__

#include "Animator.h"
#include "SpriteComponent.h"

#include <memory>

#include <string>

namespace MA
{
    class Animator;

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
