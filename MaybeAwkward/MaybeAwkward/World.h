#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

#include "GameLogic.h"

namespace MA
{
	class Entity;
    class GraphicWrapper;

    typedef std::list<std::shared_ptr<Entity>> EntityContainer;
    typedef EntityContainer::iterator EntityIterator;
    typedef EntityContainer EntityList;

    class World
    {
	public:
		static World instance;

        void init()
        {
            mGameplay = std::make_shared<GameLogic>();
            init_gameplay(mGameplay.get());
        }

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
        

        void step(float dt);
	private:
        std::shared_ptr<GraphicWrapper> mGW;

		EntityContainer mEverybodyList;

        std::shared_ptr<MA::GameLogic> mGameplay;

    };
}

#endif // World_h__
