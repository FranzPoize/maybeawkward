#include "AIFlyingInPenisFormation.h"
#include "constants.h"
#include "MessageReceiver.h"
#include "MoveMessage.h"
#include "ClanLib/core.h"

#include <memory>

using namespace MA;

AIFlyingInPenisFormation::AIFlyingInPenisFormation()
{
	mTimeFromStart = 0.0f;
}

void AIFlyingInPenisFormation::update(MessageReceiver &aMessageReceiver,float dt)
{
	//create message with xDiff = mXSpeed and yDiff = cos(mXSpeed)
	cl_log_event("info", " mxSpeed : %1 yspeed : %2 xaccel : %3 yaccel : %4",SINUS_STYLE_MOVEMENT_SPEED,SINUS_STYLE_MOVEMENT_SPEED*cos(2*3.14f*mTimeFromStart/2000),SINUS_STYLE_MOVEMENT_SPEED*dt,SINUS_STYLE_MOVEMENT_SPEED*cos(2*3.14f*mTimeFromStart/2000)*dt);
	aMessageReceiver.receiveMessage(std::make_shared<MoveMessage>(0.0f,SINUS_STYLE_MOVEMENT_SPEED*cos(2*3.14f*mTimeFromStart/2000)*dt,false));
}