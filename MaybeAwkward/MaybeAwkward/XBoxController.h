#ifndef XBoxController_h__
#define XBoxController_h__

#include <XInput.h>
#pragma comment(lib,"XInput.lib")

#include "Controller.h"

namespace AB
{

class XBoxController : public Controller
{
public:
    XBoxController(int aControllerId=0);
    void update(Entity &aEntity, float dt);

protected:
    DWORD updateState();
    bool isConnected();
    void vibrate(int leftVal = 0, int rightVal = 0);

private:
    XINPUT_STATE mControllerState;
    int mControllerNum;
};

}
#endif // XBoxController_h__
