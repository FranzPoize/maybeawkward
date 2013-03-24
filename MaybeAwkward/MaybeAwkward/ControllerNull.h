#ifndef ControllerNull_h__
#define ControllerNull_h__

#include "Controller.h"
#include "MessageReceiver.h"
#include "MoveMessage.h"

#include <memory>

namespace MA
{
class ControllerNull : public Controller
{
    void update(MessageReceiver &aReceiver, float dt)
    {
        aReceiver.receiveMessage( std::make_shared<MoveMessage>(0.f, 0.f, false) );
    }
};
}
#endif // ControllerNull_h__
