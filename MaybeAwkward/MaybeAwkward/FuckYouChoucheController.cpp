#include "Entity.h"
#include "FuckYouChoucheController.h"

using namespace MA;

FuckYouChoucheController::FuckYouChoucheController(CL_InputContext aIc):
	mIc(aIc)
{
}

void FuckYouChoucheController::update(Entity &aEntity, float dt)
{
	if(mIc.get_keyboard().get_keycode(CL_KEY_RIGHT))
	{
		//aEntity.move(dt,1,false);
	}
}