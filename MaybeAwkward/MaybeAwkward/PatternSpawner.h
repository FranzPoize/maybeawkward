#ifndef PatternSpawner_h__
#define PatternSpawner_h__
#include "Pattern.h"

namespace MA
{
class GraphicWrapper;
class Entity;
class PatternSpawner
{
public:
	PatternSpawner(Entity &aEntity):
	  mEntity(aEntity)
	  {}
	void spawnAPattern(unsigned int lvl,Pattern::ControllerType type,GraphicWrapper &gw);
private:
	void spawnLevelOne(Pattern::ControllerType type,GraphicWrapper &gw);
	void spawnLevelTwo(Pattern::ControllerType type,GraphicWrapper &gw);
	void spawnLevelThree(Pattern::ControllerType type,GraphicWrapper &gw);
	Entity &mEntity;
};
}

#endif