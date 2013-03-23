#ifndef AIFlyingInPenisFormation_h__
#define AIFlyingInPenisFormation_h__

#include "Controller.h"

namespace MA
{
class MessageReceiver;

class AIFlyingInPenisFormation : public Controller
{
public:
	AIFlyingInPenisFormation();
	void update(MessageReceiver &aMessageReceiver, float dt);
private:
	float mXSpeed;
	float mTimeFromStart;
};
}
#endif