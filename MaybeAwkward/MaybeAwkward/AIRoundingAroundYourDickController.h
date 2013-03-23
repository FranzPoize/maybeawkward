#ifndef AIRoundingAroundYourDickController_h__
#define AIRoundingAroundYourDickController_h__

#include "Controller.h"

namespace MA
{
class Entity;
class MessageReceiver;
class AIRoundingAroundYourDickController : public Controller
{
public:
	AIRoundingAroundYourDickController(Entity &aTarget);
	void update(MessageReceiver &aMessageReceiver, float dt);
private:
	Entity &mTarget;
	float mTimeFromStart;
	float mCurrentXSpeed;
	float mCurrentYSpeed;
};
}
#endif