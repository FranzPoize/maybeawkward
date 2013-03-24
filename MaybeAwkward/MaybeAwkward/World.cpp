#include "World.h"

#include "Entity.h"
#include "Camera.h"
#include "GraphicWrapper.h"

using namespace MA;

World World::instance;

void World::step(float dt)
{
    mGameplay->update(dt);
    PhysicsSystem::update(dt);

    for (EntityIterator entityIt = everybodyList().begin();
        entityIt != everybodyList().end();
        ++entityIt)
    {
        (*entityIt)->update(dt);

    }

	if (everybodyList().size() < 100 && (rand() % 100) > 95)
	{
		if(mGW->camera().pos() < 1280 * 2) {
			spawner->spawnAPattern(0,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%2))),*mGW);
		}
	}
            
    getGraphicWrapper().camera().update();

    for (EntityIterator entityIt = everybodyList().begin();
        entityIt != everybodyList().end();
        ++entityIt)
    {
        (*entityIt)->draw();
    }
}