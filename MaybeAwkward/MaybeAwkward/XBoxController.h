#ifndef XBoxController_h__
#define XBoxController_h__

#include "Controller.h"

#ifdef WIN32
#include <XInput.h>
#pragma comment(lib,"XInput.lib")

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

#else

namespace AB
{

#define DWORD int

class DummyController : public Controller
{
public:
    DummyController(int aControllerId=0);
    void update(Entity &aEntity, float dt);

protected:
    DWORD updateState();
    bool isConnected();
    void vibrate(int leftVal = 0, int rightVal = 0);

private:
};


#endif // win32

}
#endif // XBoxController_h__
