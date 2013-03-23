#include "AIFlyingInPenisFormation.h"
#include "constants.h"
#include "MessageReceiver.h"
#include "MoveMessage.h"

#include <memory>

using namespace MA;

AIFlyingInPenisFormation::AIFlyingInPenisFormation()
{
	mTimeFromStart = 0.0f;
}

void AIFlyingInPenisFormation::update(MessageReceiver &aMessageReceiver,float dt)
{
	//create message with xDiff = mXSpeed and yDiff = cos(mXSpeed)
	mTimeFromStart += dt;
	aMessageReceiver.receiveMessage(std::make_shared<MoveMessage>(0.0f,SINUS_STYLE_MOVEMENT_SPEED*cos(2*3.14f*mTimeFromStart/2)*dt,false));
}