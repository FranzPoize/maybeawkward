#ifdef WIN32
#include <iostream>
#include <Windows.h>

#include <cmath>

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

#include "XBoxController.h"

#include "Entity.h"


using namespace MA;


XBoxController::XBoxController(int aControllerId) :
    mControllerNum(aControllerId)
{
}
    
void XBoxController::update(Entity &aEntity, float dt)
{
    int enter = CL_System::get_time();
    if (updateState()==ERROR_SUCCESS)
    {
        float xInput = 0.f;

        float LX = mControllerState.Gamepad.sThumbLX;
        float LY = mControllerState.Gamepad.sThumbLY;

        //determine how far the controller is pushed
        float lMagnitude = sqrt(LX*LX + LY*LY);

        //check if the controller is outside a circular dead zone
        if (lMagnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
        {
            //clip the lMagnitude at its expected maximum value
            if (lMagnitude > 32767) lMagnitude = 32767;

            //adjust lMagnitude relative to the end of the dead zone
            lMagnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

            float dampener = LX > 0 ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE+1;
            xInput = (LX+dampener)/float(32767-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
        }
        else //if the controller is in the deadzone zero out the lMagnitude
        {
            lMagnitude = 0.0;
        }

        //bool left = false;
        //bool right = false;
        //bool jump = false;

        //if (LX < 0 && lMagnitude > 0) left = true;
        //else if (LX > 0 && lMagnitude > 0) right = true;
        //// REV: redondant
        //else 
        //{
        //    left = false;
        //    right = false;
        //}


        //CL_Console::write_line("Value : %1", xInput);
        int middle = CL_System::get_time();

        WORD buttons = mControllerState.Gamepad.wButtons;
        bool jump = buttons & XINPUT_GAMEPAD_A;

        aEntity.move(dt, xInput, jump);
        int end = CL_System::get_time();
        cl_log_event("info", "\t update details : state:%1, move:%2", middle-enter, end-middle);
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
