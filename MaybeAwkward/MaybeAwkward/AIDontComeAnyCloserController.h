#ifndef AIDontComeAnyCloserController_h__
#define AIDontComeAnyCloserController_h__

#include "Controller.h"

namespace MA
{
class Entity;
class MessageReceiver;
class AIDontComeAnyCloserController : public Controller
{
public:
	AIDontComeAnyCloserController(Entity &aTarget);
	void update(MessageReceiver &aMessageReceiver, float dt);
private:
	Entity &mTarget;
};
}
#endif