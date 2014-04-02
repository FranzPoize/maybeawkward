#ifndef FuckYouChoucheController_h__
#define FuckYouChoucheController_h__

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "Controller.h"

namespace MA
{
class MessageReceiver;
class FuckYouChoucheController : public Controller
{
public:
    FuckYouChoucheController(clan::InputContext aIc);
    void update(MessageReceiver &aEntity, float dt);

private:
	clan::InputContext mIc;
};

}
#endif // XBoxController_h__
