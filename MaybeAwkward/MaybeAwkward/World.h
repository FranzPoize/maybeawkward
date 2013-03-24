#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

#include "GameLogic.h"

namespace MA
{
    std::shared_ptr<Entity> createDefaultEntity(const std::string &aRelativeFilepath, float aX, float aY);

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
		};

        void addTerrain(TerrainValue);
        
        void step(float dt);
	private:
        std::shared_ptr<GraphicWrapper> mGW;

		EntityContainer mEverybodyList;
		EntityContainer mTerrainList;

        unsigned int mLastTerrainId;
        std::shared_ptr<MA::GameLogic> mGameplay;

    };
}

#endif // World_h__
