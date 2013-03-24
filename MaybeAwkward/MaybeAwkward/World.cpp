#include "World.h"

#include "Entity.h"
#include "Camera.h"
#include "GraphicWrapper.h"

#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "DeletionHandlerTerrain.h"

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
    mGameplay->update(dt);
    PhysicsSystem::update(dt);

	if (everybodyList().size() < 100 && (rand() % 100) > 95)
	{
		if(mGW->camera().pos() < 1280 * 2) {
			spawner->spawnAPattern(0,static_cast<Pattern::ControllerType>((int)floor(static_cast<float>(rand()%2))),*mGW);
		}
	}
            
    updateTraversal(mEverybodyList, dt);
    updateTraversal(mTerrainList, dt);

    getGraphicWrapper().camera().update();

    drawTraversal(mTerrainList);
    drawTraversal(mEverybodyList);
}

void World::addTerrain(TerrainValue)
{
    std::shared_ptr<Entity> entity = createDefaultEntity("design_export/level/level1.png", (float)mLastTerrainId*WIN_WIDTH, 0.f);
    entity->setDeletionHandler(std::make_shared<DeletionHandlerTerrain>());
    mTerrainList.push_back(entity);
    ++mLastTerrainId; 
}
void World::init()
{
        mGameplay = std::make_shared<GameLogic>();
        init_gameplay(mGameplay.get());

        mLastTerrainId = 0;
        addTerrain(UN);
        addTerrain(UN);
        addTerrain(UN);
}
namespace MA
{

std::shared_ptr<Entity> createDefaultEntity(const std::string &aRelativeFilepath, float aX, float aY)
{
    CL_SpriteDescription proxyDescription;
    proxyDescription.add_frame(ASSET_PATH+aRelativeFilepath);

    CL_Sprite proxySprite(World::instance.getGraphicWrapper().cl(), proxyDescription);
    proxySprite.set_alignment(origin_top_left);
    std::shared_ptr<Drawer> proxyDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), proxySprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
    std::shared_ptr<Entity> proxy = std::make_shared<Entity>(controllerNull, proxyDrawer);

    PhysicsMaterial proxyMaterial(EPSILON, EPSILON, 10000.f, 13, 13);
    PhysicsSystem::addEntity(*proxy, PHYSICS_BOX);
    PhysicsSystem::setPosition(proxy->physicsID(), aX, aY);

    return proxy;
}

}