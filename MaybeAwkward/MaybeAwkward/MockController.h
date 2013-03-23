#ifndef MockController_h__
#define MockController_h__

#include "Controller.h"

namespace MA
{

class Entity;

class MockController : public Controller
{
public:
    virtual void update(MessageReceiver &aReceiver, float dt) override {};
};

}
#endif // Controller_h__
