#ifndef BackgroundPlanFourManager_h__
#define BackgroundPlanFourManager_h__

#include "constants.h"

#include <list>
#include <memory>
namespace MA
{
class TerrainWrapper;
class BackgroundPlanFourManager
{
public:
	BackgroundPlanFourManager();
	void addTerrain();
private:
	std::list<std::shared_ptr<TerrainWrapper>> mTerrainPool;
	int mLastTerrainId;
	std::shared_ptr<TerrainWrapper> createDefaultEntity(const std::string &aRelativeFilepath);
	const static float cameraFactor;
};
}

#endif