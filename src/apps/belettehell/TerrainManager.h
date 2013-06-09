#ifndef TerrainManager_h__
#define TerrainManager_h__

#include <list>
#include <memory>
namespace MA
{
class TerrainWrapper;
class TerrainManager
{
public:
	TerrainManager();
	void addTerrain();
private:
	std::list<std::shared_ptr<TerrainWrapper>> mTerrainPool;
	int mLastTerrainId;
	std::shared_ptr<TerrainWrapper> createDefaultEntity(const std::string &aRelativeFilepath);
};
}

#endif