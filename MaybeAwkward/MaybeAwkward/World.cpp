#include "World.h"

#include "Entity.h"
#include "Camera.h"
#include "GraphicWrapper.h"

#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "DeletionHandlerTerrain.h"
#include "AttackerBullet.h"

#include "SpawnPoint.h"

#include "constants.h"

#include <memory>

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

	if (everybodyList().size() < 400 && (rand() % 100) > 95)
	{
		if(mGW->camera().pos() < 1280 * 4) 
		{
			spawner->spawnAPattern(0,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%3))),*mGW,SpawnPoint::NORMAL);
		}
		else if(mGW->camera().pos() < 1280 * 8) 
		{
			spawner->spawnAPattern(1,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%3))),*mGW,SpawnPoint::HIGH);
		}
		else
		{
			spawner->spawnAPattern(2,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%3))),*mGW,SpawnPoint::HIGHER);
		}
	}
            
    updateTraversal(mEverybodyList, dt);
    updateTraversal(mTerrainList, dt);
	updateTraversal(mBackgroundThreeList, dt);
	updateTraversal(mBackgroundFourList, dt);

    getGraphicWrapper().camera().update();

	drawTraversal(mSkyBackground);
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

		createBackground();
}

void World::createBackground() {
	CL_SpriteDescription proxyDescription;
    proxyDescription.add_frame(ASSET_PATH+"design_export/ciel.png");

    CL_Sprite proxySprite(World::instance.getGraphicWrapper().cl(), proxyDescription);
    proxySprite.set_alignment(origin_top_left);
    std::shared_ptr<Drawer> proxyDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), proxySprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
	std::shared_ptr<Entity> sky = std::make_shared<Entity>(controllerNull, proxyDrawer);
	sky->setCameraFactor(0.f);

	sky->setDeletionHandler(std::make_shared<DeletionHandlerTerrain>());

    PhysicsSystem::addEntity(*sky, PHYSICS_BOX);

	mSkyBackground.push_back(sky);

	CL_SpriteDescription proxyDescriptionSun;
    proxyDescriptionSun.add_frame(ASSET_PATH+"design_export/soleil.png");

    CL_Sprite proxySpriteSun(World::instance.getGraphicWrapper().cl(), proxyDescriptionSun);
    proxySpriteSun.set_alignment(origin_top_left);
    std::shared_ptr<Drawer> proxySunDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), proxySpriteSun);

	std::shared_ptr<Entity> sun = std::make_shared<Entity>(controllerNull, proxySunDrawer);
	sun->setCameraFactor(0.f);

	sun->setDeletionHandler(std::make_shared<DeletionHandlerTerrain>());

    PhysicsSystem::addEntity(*sun, PHYSICS_BOX);
	PhysicsSystem::setPosition(sun->physicsID(),400.f,215.f);

	mSkyBackground.push_back(sun);

	CL_SpriteDescription proxyDescriptionRay;
    proxyDescriptionRay.add_frame(ASSET_PATH+"design_export/rayon_soleil.png");

    CL_Sprite proxySpriteRay(World::instance.getGraphicWrapper().cl(), proxyDescriptionRay);
    proxySpriteRay.set_alignment(origin_top_left);
    std::shared_ptr<Drawer> proxyRayDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), proxySpriteRay);

	std::shared_ptr<Entity> ray = std::make_shared<Entity>(controllerNull, proxyRayDrawer);
	sun->setCameraFactor(0.f);

	sun->setDeletionHandler(std::make_shared<DeletionHandlerTerrain>());

    PhysicsSystem::addEntity(*ray, PHYSICS_BOX);
	PhysicsSystem::setPosition(ray->physicsID(),0.f,0.f);

	mSkyBackground.push_back(ray);
}