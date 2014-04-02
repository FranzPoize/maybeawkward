#include <string>

#include "SpriteComponent.h"
#include "GraphicWrapper.h"


using namespace MA;


SpriteComponent::SpriteComponent(GraphicWrapper &gc, std::string resourceFileName)
{
    clan::ResourceManager resources(resourceFileName);
    std::vector<clan::String> listOfDrawable = resources.get_resource_names_of_type("sprite");
    for(std::size_t i=0;i<listOfDrawable.size();++i) {
        clan::Sprite sprite(gc.cl(), listOfDrawable[i], &resources);
        addDrawer(listOfDrawable[i],std::make_shared<MA::DrawerSprite>(gc, sprite));
    }
}

void SpriteComponent::addDrawer(std::string drawerName, std::shared_ptr<MA::DrawerSprite> drawer)
{
    drawersList[drawerName] = drawer;
}


std::shared_ptr<MA::DrawerSprite> SpriteComponent::getDrawer(std::string drawerName)
{
    return drawersList[drawerName];
}