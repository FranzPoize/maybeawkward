#include "AnimatorSpriteSwitcher.h"

#include "World.h"
#include "GraphicWrapper.h"
#include "Entity.h"

using namespace MA;

AnimatorSpriteSwitcher::AnimatorSpriteSwitcher(const std::string &aRessourcesfile)
{
    mSpriteComponent.reset(new SpriteComponent(World::instance.getGraphicWrapper(), aRessourcesfile));
}

void AnimatorSpriteSwitcher::animate(Entity &aEntity)
{
    AnimState aState = aEntity.checkStateChange();
    if(aState != NO_CHANGE)
    {
        aEntity.setDrawer(mSpriteComponent->getDrawer(animEnumToNounoursStr(aState)));
        clan::Console::write_line("anim : %1", animEnumToNounoursStr(aState));
        if(aState== IDLE)
        {
            int i = 5;
        }
    }
}