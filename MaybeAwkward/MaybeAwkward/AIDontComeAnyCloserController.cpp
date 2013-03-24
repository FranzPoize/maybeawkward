#include "AIDontComeAnyCloserController.h"
#include "Entity.h"
#include "constants.h"
#include "MessageReceiver.h"
#include "MoveMessage.h"
#include <cmath>

using namespace MA;

AIDontComeAnyCloserController::AIDontComeAnyCloserController(Entity &aTarget):
	mTarget(aTarget)
{
}

	void AIDontComeAnyCloserController::update(MessageReceiver &aMessageReceiver,float dt)
{
	//calculate distance from target
	float radius = sqrt(pow(mTarget.x() - dynamic_cast<Entity&>(aMessageReceiver).x(),2) + pow(mTarget.y() - dynamic_cast<Entity&>(aMessageReceiver).y(),2));
	
	float forceValue = ORBITAL_ENEMY_WEIGHT/radius*radius;

	//if target close enough -> rape its ass
	if(radius < AI_REACTION_DISTANCE)
	{
		float xComponent = dt*forceValue * AI_ATTRACTION_TO_TARGET * (mTarget.x() - dynamic_cast<Entity&>(aMessageReceiver).x()) / radius;
		float yComponent = dt*forceValue * AI_ATTRACTION_TO_TARGET * (mTarget.y() - dynamic_cast<Entity&>(aMessageReceiver).y()) / radius;

		return aMessageReceiver.receiveMessage(std::make_shared<MoveMessage>(xComponent,yComponent,false));
	}
}