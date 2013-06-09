#include "TerrainManager.h"
#include "TerrainWrapper.h"
#include "Entity.h"
#include "World.h"
#include "DrawerSprite.h"
#include "ControllerNull.h"
#include "DeletionHandlerTerrain.h"
#include "GraphicWrapper.h"

#include "constants.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>

using namespace MA;

TerrainManager::TerrainManager()
{
	for (int i = 1;i<7;i++)
	{
		std::ostringstream str;
		str << "design_export/level/level" << i << ".png";
		std::shared_ptr<TerrainWrapper> entityOne = createDefaultEntity(str.str());
		std::shared_ptr<TerrainWrapper> entityTwo = createDefaultEntity(str.str());
        entityOne->families().push_back(TERRAIN);
        entityTwo->families().push_back(TERRAIN);
		mTerrainPool.push_back(entityOne);
		mTerrainPool.push_back(entityTwo);
	}
	mLastTerrainId = 0;
}

std::shared_ptr<TerrainWrapper> TerrainManager::createDefaultEntity(const std::string &aRelativeFilepath)
{
    CL_SpriteDescription proxyDescription;
    proxyDescription.add_frame(ASSET_PATH+aRelativeFilepath);

    CL_Sprite proxySprite(World::instance.getGraphicWrapper().cl(), proxyDescription);
    proxySprite.set_alignment(origin_top_left);
    std::shared_ptr<Drawer> proxyDrawer = std::make_shared<DrawerSprite>(World::instance.getGraphicWrapper(), proxySprite);

    std::shared_ptr<Controller> controllerNull = std::make_shared<ControllerNull>();
	std::shared_ptr<TerrainWrapper> proxy = std::make_shared<TerrainWrapper>(controllerNull, proxyDrawer);

	proxy->setDeletionHandler(std::make_shared<DeletionHandlerTerrain>());

    PhysicsMaterial proxyMaterial(EPSILON, EPSILON, 10000.f, 13, 13);
    PhysicsSystem::addEntity(*proxy, PHYSICS_BOX);

    return proxy;
}

void TerrainManager::addTerrain()
{
	bool notSelected = true;
	while(notSelected)
	{
		int terrainNumber = rand()%11;
		std::list<std::shared_ptr<TerrainWrapper>>::iterator terrainIt = mTerrainPool.begin();
		for(int i = 0;i<terrainNumber;i++) terrainIt++;

		if(!((*terrainIt)->isOccupied()))
		{
			notSelected = false;
			(*terrainIt)->setX((float)WIN_WIDTH*mLastTerrainId);
			(*terrainIt)->setOccupied(true);
			World::instance.terrainList().push_back((*terrainIt));
			cl_log_event("info","Creation terrain. mLastTerrainId %1 x: %2, entityX: %3",mLastTerrainId,(float)WIN_WIDTH*mLastTerrainId,(*terrainIt)->x());
			mLastTerrainId++;
		}
	}
}
