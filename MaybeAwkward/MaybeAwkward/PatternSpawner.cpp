#include "PatternSpawner.h"
#include "Pattern.h"
#include "MultipleSpawnPattern.h"
#include <memory>
#include <vector>
#include "SpawnPoint.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "Camera.h"

using namespace MA;

void PatternSpawner::spawnLevelOne(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType)
{
	std::vector<SpawnPoint> spawnVector;
	for (int i = 1; i < 4;i++)
	{
		spawnVector.push_back(SpawnPoint(eType,WIN_WIDTH+20.0f+gw.camera().pos(),(WIN_HEIGHT/4)*i,-SINUS_STYLE_MOVEMENT_SPEED,0.0f));
	}

	MultipleSpawnPattern pattern(mEntity,type,spawnVector);

	pattern.launchPattern(gw);
}

void PatternSpawner::spawnLevelTwo(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType)
{
	std::vector<SpawnPoint> spawnVector;
	for (int i = 1; i < 8;i++)
	{
		spawnVector.push_back(SpawnPoint(eType,WIN_WIDTH+20.0f+gw.camera().pos(),(WIN_HEIGHT/8)*i,-SINUS_STYLE_MOVEMENT_SPEED,0.0f));
	}

	MultipleSpawnPattern pattern(mEntity,type,spawnVector);

	pattern.launchPattern(gw);
}

void PatternSpawner::spawnLevelThree(Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType)
{
	std::vector<SpawnPoint> spawnVector;
	for (int i = 1; i < 12;i++)
	{
		spawnVector.push_back(SpawnPoint(eType,WIN_WIDTH+20.0f+gw.camera().pos(),(WIN_HEIGHT/12)*i,-SINUS_STYLE_MOVEMENT_SPEED,0.0f));
	}

	MultipleSpawnPattern pattern(mEntity,type,spawnVector);

	pattern.launchPattern(gw);
}

void PatternSpawner::spawnAPattern(unsigned int lvl,Pattern::ControllerType type,GraphicWrapper &gw,SpawnPoint::EnemyType eType)
{
	if (lvl == 1)
	{
		spawnLevelOne(type,gw,eType);
	}
	else if (lvl == 2)
	{
		spawnLevelTwo(type,gw,eType);
	}
	else
	{
		spawnLevelThree(type,gw,eType);
	}
}
