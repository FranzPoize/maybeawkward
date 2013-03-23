#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

namespace MA
{
	class Entity;
    class GraphicWrapper;


    class World
    {
	public:
		static World instance;

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

        typedef std::list<std::shared_ptr<Entity>> EntityContainer;
        typedef EntityContainer::iterator EntityIterator;
		EntityContainer mEverybodyList;

    };
}

#endif // World_h__
