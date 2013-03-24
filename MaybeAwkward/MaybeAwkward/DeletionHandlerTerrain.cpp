#include "DeletionHandlerTerrain.h"
#include "TerrainWrapper.h"
#include "GraphicWrapper.h"
#include "Camera.h"
#include "World.h"

#include "ClanLib/core.h"
#include "ClanLib/application.h"

using namespace MA;

bool DeletionHandlerTerrain::deletion(Entity &aEntity)
{
	if((aEntity.x() + 1280)/aEntity.cameraFactor() < World::instance.getGraphicWrapper().camera().pos())
	{
		if(aEntity.cameraFactor() > 0.5f)
			World::instance.terrainManager()->addTerrain();
		else if (aEntity.cameraFactor() >0.3f)
			World::instance.bThreeManager()->addTerrain();
		else if (aEntity.cameraFactor() >0.1f)
			World::instance.bFourManager()->addTerrain();
			
		TerrainWrapper &terrain = dynamic_cast<TerrainWrapper&>(aEntity);
		terrain.setOccupied(false);
		return true;
	}

	return false;
}
