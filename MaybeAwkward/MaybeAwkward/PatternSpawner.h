#ifndef PatternSpawner_h__
#define PatternSpawner_h__
#include "Pattern.h"

#include "SpawnPoint.h"

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
	void spawnAPattern(unsigned int lvl,Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType);
private:
	void spawnLevelOne(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType);
	void spawnLevelTwo(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType);
	void spawnLevelThree(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType);
	Entity &mEntity;
};
}

#endif