#include "MultipleSpawnPattern.h"
#include "SpawnPoint.h"
#include "Entity.h"
#include "Controller.h"
#include "AIDontComeAnyCloserController.h"
#include "AIFlyingInPenisFormation.h"
#include "AIRoundingAroundYourDickController.h"
#include "DrawerSprite.h"
#include "GraphicWrapper.h"
#include "constants.h"
#include "ClanLib/core.h"
#include "ClanLib/display.h"
#include "World.h"
#include <vector>
#include <memory>

using namespace MA;

MultipleSpawnPattern::MultipleSpawnPattern(Entity &aTarget,MultipleSpawnPattern::ControllerType aControllerType,std::vector<SpawnPoint> &aSpawnPointArray):
	mControllerType(aControllerType),
	mSpawnPointArray(aSpawnPointArray),
	mTarget(aTarget)
{
}

void MultipleSpawnPattern::launchPattern(GraphicWrapper &gw) {

	for(std::vector<SpawnPoint>::iterator i = mSpawnPointArray.begin();
		i != mSpawnPointArray.end();
		i++)
	{
		std::shared_ptr<Controller> controller;
		switch(mControllerType)
		{
		case AROUND:
			controller = std::make_shared<AIRoundingAroundYourDickController>(mTarget);
			break;
		case CLOSE:
			controller = std::make_shared<AIDontComeAnyCloserController>(mTarget);
			break;
		case FORMATION:
			controller = std::make_shared<AIFlyingInPenisFormation>();
			break;
		default:
			break;
		}

		std::shared_ptr<Entity> enemy;
		clan::SpriteDescription enemyDescription;

		switch(i->mType)
		{
		case SpawnPoint::NORMAL:
			
			enemyDescription.add_frame(ASSET_PATH+"design_export/ennemi/sprite_skybull_vert_00.png");
			break;
		case SpawnPoint::HIGH:
			
			enemyDescription.add_frame(ASSET_PATH+"design_export/ennemi/sprite_skybull_00.png");
			break;
		case SpawnPoint::HIGHER:
			
			enemyDescription.add_frame(ASSET_PATH+"design_export/ennemi/sprite_skybull_rouge_00.png");
			break;
		}
		clan::Sprite enemySprite(gw.cl(),enemyDescription);
		enemySprite.set_alignment(ORIGIN);

		std::shared_ptr<DrawerSprite> drawer(new DrawerSprite(gw,enemySprite));
		enemy = std::make_shared<Entity>(controller,drawer);
		enemy->families().push_back(ENEMY);

		PhysicsMaterial mat(1.0,1.0,1.0, 100., 100.); // TODO actual sizes
		MA::PhysicsSystem::addEntity(*enemy,MA::PHYSICS_BOX, &mat);
		enemy->setPosition(i->x, i->y);
		enemy->getPhysicalObject()->setXVelocity(i->xSpeed);
		enemy->getPhysicalObject()->setYVelocity(i->ySpeed);

		World::instance.everybodyList().push_back(enemy);
	}
}