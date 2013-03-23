#include "AIFlyingInPenisFormation.h"
#include "constants.h"

using namespace MA;

AIFlyingInPenisFormation::AIFlyingInPenisFormation()
{
	mXSpeed = SINUS_STYLE_MOVEMENT_SPEED;
}

void AIFlyingInPenisFormation::update(Entity &aEntity,float dt)
{
	//create message with xDiff = mXSpeed and yDiff = cos(mXSpeed)
}