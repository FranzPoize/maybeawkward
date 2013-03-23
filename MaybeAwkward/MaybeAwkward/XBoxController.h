#ifndef XBoxController_h__
#define XBoxController_h__

#include "Controller.h"

#ifdef WIN32
#include <XInput.h>
#pragma comment(lib,"XInput.lib")

#include "Controller.h"


namespace MA
{

class MessageReceiver;

class XBoxController : public Controller
{
public:
    enum ControlType
    {
        MOVE=0x01,
        LEFT_ATTACK=0x02,
        RIGHT_ATTACK=0x04
    };

    XBoxController(int aControllerId=0);
    
    void update(MessageReceiver &aReceiver, float dt);

    void switchControlType(const ControlType control)
    {
        mControlTypes = mControlTypes ^ control;
    }

protected:
    DWORD updateState();
    bool isConnected();
    void vibrate(int leftVal = 0, int rightVal = 0);

private:
    unsigned int mControlTypes;
    XINPUT_STATE mControllerState;
    int mControllerNum;
};


} // namespace

#endif // WIN32
#endif // XBoxController_h__
