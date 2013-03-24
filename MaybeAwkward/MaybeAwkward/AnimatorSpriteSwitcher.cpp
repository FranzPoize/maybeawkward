#include "AnimatorSpriteSwitcher.h"

#include "SpriteComponent.h"
#include "World.h"
#include "GraphicWrapper.h"

using namespace MA;

AnimatorSpriteSwitcher::AnimatorSpriteSwitcher(const std::string &aRessourcesfile)
{
    mSpriteComponent.reset(new SpriteComponent(World::instance.getGraphicWrapper(), aRessourcesfile));
}

void AnimatorSpriteSwitcher::animate(Entity &aEntity)
{
}