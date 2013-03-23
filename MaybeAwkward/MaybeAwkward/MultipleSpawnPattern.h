#ifndef MultipleSpawnPattern_h__
#define MultipleSpawnPattern_h__

#include "Pattern.h"
#include <vector>
namespace MA
{
class SpawnPoint;
class Entity;
class Controller;
class GraphicWrapper;
class MultipleSpawnPattern : public Pattern
{
public:
	MultipleSpawnPattern(Entity &aTarget,ControllerType aControllerType,std::vector<SpawnPoint> &aSpawnPointArray);
	void launchPattern(GraphicWrapper &gw);
private:
	void spawnEnemy(Entity &enemy,Controller &enemyController, float x, float y);
	ControllerType mControllerType;
	std::vector<SpawnPoint> &mSpawnPointArray;
	Entity &mTarget;
};
}
#endif