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
	if((aEntity.x() + 1280) < World::instance.getGraphicWrapper().camera().pos())
	{
		World::instance.terrainManager()->addTerrain();
		TerrainWrapper &terrain = dynamic_cast<TerrainWrapper&>(aEntity);
		cl_log_event("info","Supperssion terrain","");
		terrain.setOccupied(false);
		return true;
	}

	return false;
}
