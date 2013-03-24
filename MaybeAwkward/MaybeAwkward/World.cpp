#include "World.h"

#include "Entity.h"
#include "Camera.h"
#include "GraphicWrapper.h"

#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "DeletionHandlerTerrain.h"
#include "AttackerBullet.h"

#include "constants.h"

using namespace MA;

World World::instance;

void updateTraversal(EntityList &aList, float dt)
{
    for (EntityIterator entityIt = aList.begin();
        entityIt != aList.end();)
    {
        if ((*entityIt)->update(dt))
        {
            entityIt = aList.erase(entityIt);
        }
        else
        {
            ++entityIt;
        }
    }
}

void drawTraversal(EntityList &aList)
{
    for (EntityIterator entityIt = aList.begin();
        entityIt != aList.end();
        ++entityIt)
    {
        (*entityIt)->draw();
    }
}
   
void World::step(float dt)
{
    //mGameplay->update(dt);
    PhysicsSystem::update(dt);

	if (everybodyList().size() < 100 && (rand() % 100) > 95)
	{
		if(mGW->camera().pos() < 1280 * 2) {
			spawner->spawnAPattern(0,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%3))),*mGW);
		}
	}
            
    updateTraversal(mEverybodyList, dt);
    updateTraversal(mTerrainList, dt);
	updateTraversal(mBackgroundThreeList, dt);
	updateTraversal(mBackgroundFourList, dt);

    getGraphicWrapper().camera().update();

	drawTraversal(mBackgroundFourList);
	drawTraversal(mBackgroundThreeList);
    drawTraversal(mTerrainList);
    drawTraversal(mEverybodyList);
	
}

void World::init()
{
        mGameplay = std::make_shared<GameLogic>();
        init_gameplay(mGameplay.get());
		mTerrainManager = std::make_shared<TerrainManager>();
		mBThreeManager = std::make_shared<BackgroundPlanThreeManager>();
		mBFourManager = std::make_shared<BackgroundPlanFourManager>();

        gBulletPool.reset(new BulletPool());

		mTerrainManager->addTerrain();
		mTerrainManager->addTerrain();
		mTerrainManager->addTerrain();

		mBThreeManager->addTerrain();
		mBThreeManager->addTerrain();
		mBThreeManager->addTerrain();

		mBFourManager->addTerrain();
		mBFourManager->addTerrain();
		mBFourManager->addTerrain();
}