#ifndef MockController_h__
#define MockController_h__

#include "Controller.h"
#include "AttackMessage.h"

namespace MA
{

class Entity;

class MockController : public Controller
{
public:
    virtual void update(MessageReceiver &aReceiver, float dt) override {
        // aReceiver.receiveMessage( std::make_shared<AttackMessage>(AttackMessage(true, 0)));
    };
};

}
#endif // Controller_h__
