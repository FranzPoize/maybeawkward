#include "World.h"

#include "Entity.h"
#include "Camera.h"
#include "GraphicWrapper.h"

using namespace MA;

World World::instance;

void World::step(float dt)
{
    for (EntityIterator entityIt = everybodyList().begin();
        entityIt != everybodyList().end();
        ++entityIt)
    {
        (*entityIt)->update(dt);

    }
            
    getGraphicWrapper().camera().update();

    for (EntityIterator entityIt = everybodyList().begin();
        entityIt != everybodyList().end();
        ++entityIt)
    {
        (*entityIt)->draw();
    }
}