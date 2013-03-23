#include "AIRoundingAroundYourDickController.h"
#include "Entity.h"
#include "constants.h"

using namespace MA;

AIRoundingAroundYourDickController::AIRoundingAroundYourDickController(Entity &aTarget):
	mTarget(aTarget)
{
	mTimeFromStart = 0;
	mCurrentXSpeed = 0;
	mCurrentYSpeed = 0;
}

void AIRoundingAroundYourDickController::update(Entity &aEntity,float dt)
{
	//distance between target and entity
	float radius = sqrt(pow(mTarget.x() - aEntity.x(),2) + pow(mTarget.y() - aEntity.y(),2));

	//Strength of the pull on entity
	float forceValue = (ORBITAL_ENEMY_WEIGHT + ORBITAL_PLAYER_WEIGHT)/radius;

	float xComponent = (mTarget.x() - aEntity.x()) / radius;
	float yComponent = (mTarget.y() - aEntity.y()) / radius;

	if (mTimeFromStart == 0)
	{
		//Initialize Starting speed perpendicular to target
		mCurrentXSpeed = -yComponent * ORBITAL_STARTING_SPEED;
		mCurrentYSpeed = xComponent * ORBITAL_STARTING_SPEED;
	}

	mTimeFromStart += dt;

	float xForceComponent = forceValue * xComponent;
	float yForceComponent = forceValue * yForceComponent;

	//now we calculate the new value of speed from the current time elapsed and the value of the force
	mCurrentXSpeed += xForceComponent * dt;
	mCurrentYSpeed += yForceComponent * dt;

	//generate message for physics engine

}