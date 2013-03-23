#ifndef World_h__
#define World_h__

#include <list>
#include <memory>

namespace MA
{
	class Entity;
    typedef std::list<std::shared_ptr<Entity>> EntityList;
    class World
    {
	public:
		static World instance;

		EntityList *everybodyList() {
			return &mEverybodyList;
		}
        EntityList *allEntities() {
            return &mEverybodyList;
        }
	private:
	EntityList mEverybodyList;
    };
}

#endif // World_h__
