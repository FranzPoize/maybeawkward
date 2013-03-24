#ifndef BackgroundPlanThreeManager_h__
#define BackgroundPlanThreeManager_h__

#include "constants.h"

#include <list>
#include <memory>

namespace MA
{
class TerrainWrapper;
class BackgroundPlanThreeManager
{
public:
	BackgroundPlanThreeManager();
	void addTerrain();
private:
	std::list<std::shared_ptr<TerrainWrapper>> mTerrainPool;
	int mLastTerrainId;
	std::shared_ptr<TerrainWrapper> createDefaultEntity(const std::string &aRelativeFilepath);
	const static float cameraFactor;
};
}

#endif