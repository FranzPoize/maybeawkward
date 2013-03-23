#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

namespace MA
{
	class Entity;
    class World
    {
	public:
		static World instance;
		std::list<std::shared_ptr<Entity>> *everybodyList()
		{
			return &mEverybodyList;	
		};
	private:
		std::list<std::shared_ptr<Entity>> mEverybodyList;
    };
}

#endif // World_h__
