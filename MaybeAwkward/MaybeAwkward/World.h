#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

#include "GameLogic.h"
#include "PatternSpawner.h"
#include "TerrainManager.h"
#include "BackgroundPlanThreeManager.h"
#include "BackgroundPlanFourManager.h"

namespace MA
{
    class BulletPool;

   // std::shared_ptr<Entity> createDefaultEntity(const std::string &aRelativeFilepath, float aX, float aY);

	class Entity;
    class GraphicWrapper;

    typedef std::list<std::shared_ptr<Entity>> EntityContainer;
    typedef EntityContainer::iterator EntityIterator;
    typedef EntityContainer EntityList;

    class World
    {
	public:
		static World instance;

        enum TerrainValue
        {
            UN
        };


		void createSpawner(Entity &aPibi)
		{
			spawner = std::make_shared<PatternSpawner>(aPibi);
		}

        void init();
        void setGraphicWrapper(std::shared_ptr<GraphicWrapper> aWrapper)
        {
            mGW = aWrapper;
        }
        GraphicWrapper &getGraphicWrapper()
        {
            return *mGW;
        }

		std::list<std::shared_ptr<Entity>> &everybodyList()
		{
			return mEverybodyList;	
		}

		std::list<std::shared_ptr<Entity>> &terrainList()
		{
			return mTerrainList;	
		}

		std::list<std::shared_ptr<Entity>> &backgroundThreeList()
		{
			return mBackgroundThreeList;	
		}

		std::list<std::shared_ptr<Entity>> &backgroundFourList()
		{
			return mBackgroundFourList;	
		}

		std::shared_ptr<TerrainManager> terrainManager()
		{
			return mTerrainManager;
		}

		std::shared_ptr<BackgroundPlanThreeManager> bThreeManager()
		{
			return mBThreeManager;
		}

		std::shared_ptr<BackgroundPlanFourManager> bFourManager()
		{
			return mBFourManager;
		}
        
        void step(float dt);
	private:
        std::shared_ptr<GraphicWrapper> mGW;

		EntityContainer mEverybodyList;
		EntityContainer mTerrainList;
		EntityContainer mBackgroundThreeList;
		EntityContainer mBackgroundFourList;
		
		std::shared_ptr<TerrainManager> mTerrainManager;

		std::shared_ptr<BackgroundPlanThreeManager> mBThreeManager;
		std::shared_ptr<BackgroundPlanFourManager> mBFourManager;

        std::shared_ptr<MA::GameLogic> mGameplay;

		std::shared_ptr<PatternSpawner> spawner;

    public:
        std::unique_ptr<BulletPool> gBulletPool;
    };
}

#endif // World_h__
