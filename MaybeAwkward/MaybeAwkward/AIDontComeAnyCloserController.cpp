#include "AIDontComeAnyCloserController.h"
#include "Entity.h"
#include "constants.h"

using namespace MA;

AIDontComeAnyCloserController::AIDontComeAnyCloserController(Entity &aTarget):
	mTarget(aTarget)
{
}

void AIDontComeAnyCloserController::update(Entity &aEntity,float dt)
{
	//calculate distance from target
	float radius = sqrt(pow(mTarget.x() - aEntity.x(),2) + pow(mTarget.y() - aEntity.y(),2));
	
	float forceValue = (ORBITAL_ENEMY_WEIGHT + ORBITAL_PLAYER_WEIGHT)/radius;

	//if target close enough -> rape its ass
	if(radius < AI_REACTION_DISTANCE)
	{
		float xComponent = dt*forceValue * (mTarget.x() - aEntity.x()) / radius;
		float yComponent = dt*forceValue * (mTarget.y() - aEntity.y()) / radius;

		//create message with x and y component
	}
}