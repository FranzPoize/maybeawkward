#ifndef MockController_h__
#define MockController_h__

#include "Controller.h"

namespace MA
{

class Entity;

class MockController : public Controller
{
public:
    void update(Entity &aEntity, float dt) {}
};

}
#endif // Controller_h__
