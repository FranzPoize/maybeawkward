#ifndef TerrainWrapper_h__
#define TerrainWrapper_h__

#include "Entity.h"
#include <memory>

namespace MA
{
class TerrainWrapper : public Entity
{
public:
	TerrainWrapper(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer) : Entity(aController,aDrawer)
	{
		occupied = false;
	}
	bool isOccupied()
	{
		return occupied;
	}
	void setOccupied(bool state)
	{
		occupied = state;
	}
private:
	bool occupied;
};
}

#endif