#ifdef WIN32
#include <iostream>
#include <Windows.h>
#include <intsafe.h>

#include <cmath>
#include <memory>

#include <ClanLib/core.h>

#include "XBoxController.h"
#include "MessageReceiver.h"
#include "SpeedMessage.h"
#include "AttackMessage.h"

using namespace MA;


XBoxController::XBoxController(int aControllerId) :
    mControlTypes(0),
    mControllerNum(aControllerId)
{
}
    
void XBoxController::update(MessageReceiver &aReceiver, float dt)
{
    int enter = CL_System::get_time();
    if (updateState()==ERROR_SUCCESS)
    {

        float leftAngle=0.f, rightAngle=0.f;
        bool leftAttack=false, rightAttack=false;

        if(mControlTypes & MOVE)
        {
            float leftTrigger=0.f, rightTrigger=0.f;

            BYTE LT = mControllerState.Gamepad.bLeftTrigger;
            BYTE RT = mControllerState.Gamepad.bRightTrigger;

            if (LT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                leftTrigger = float(LT)/BYTE_MAX;
            }
            if ( RT > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                rightTrigger = float(RT)/BYTE_MAX;
            }

            static const WORD JUMP_BUTTONS = XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER
                | XINPUT_GAMEPAD_LEFT_THUMB | XINPUT_GAMEPAD_RIGHT_THUMB;
            WORD buttons = mControllerState.Gamepad.wButtons;
            bool jump = buttons & JUMP_BUTTONS;

            aReceiver.receiveMessage( std::make_shared<SpeedMessage>(SpeedMessage(leftTrigger, rightTrigger, jump)) );
        }

        if (mControlTypes & LEFT_ATTACK)
        {

            float LX = mControllerState.Gamepad.sThumbLX;
            float LY = mControllerState.Gamepad.sThumbLY;


            //check if the controller is outside a circular dead zone
            if (sqrt(LX*LX + LY*LY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                leftAttack = true;
                leftAngle = -atan2(LY, LX);
            }

            aReceiver.receiveMessage( std::make_shared<AttackMessage>(AttackMessage(leftAttack, leftAngle)));
        }
        if (mControlTypes & RIGHT_ATTACK)
        {
            float RX = mControllerState.Gamepad.sThumbRX;
            float RY = mControllerState.Gamepad.sThumbRY;

            if (sqrt(RX*RX + RY*RY) > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                rightAttack = true;
                rightAngle = -atan2(RY, RX);
            }

            aReceiver.receiveMessage( std::make_shared<AttackMessage>(AttackMessage(rightAttack, rightAngle)));
        }
    }
}

DWORD XBoxController::updateState()
{
    ZeroMemory( &mControllerState, sizeof(XINPUT_STATE) );

    return XInputGetState(mControllerNum,&mControllerState);
    //if (dwResult == ERROR_SUCCESS) return mControllerState;
}

bool XBoxController::isConnected()
{
    ZeroMemory( &mControllerState, sizeof(XINPUT_STATE) );

    DWORD dwResult = XInputGetState(mControllerNum,&mControllerState);
    // loul, was success so unexpected ?
    return dwResult == ERROR_SUCCESS;
}

void XBoxController::vibrate(int leftVal, int rightVal)
{
    XINPUT_VIBRATION vibration;
    ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
    vibration.wLeftMotorSpeed = leftVal;
    vibration.wRightMotorSpeed = rightVal;
    XInputSetState( mControllerNum, &vibration );
}

#endif // WIN32
