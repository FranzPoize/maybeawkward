#include "FuckYouChoucheController.h"

#include "MessageReceiver.h"
#include "MoveMessage.h"

#include <memory>

using namespace MA;

FuckYouChoucheController::FuckYouChoucheController(clan::InputContext aIc):
	mIc(aIc)
{
}

void FuckYouChoucheController::update(MessageReceiver &aEntity, float dt)
{
	if(mIc.get_keyboard().get_keycode(clan::KEY_RIGHT))
	{
		aEntity.receiveMessage( std::make_shared<MoveMessage>(0.f, 1.f, false) );
	} else {
		aEntity.receiveMessage( std::make_shared<MoveMessage>(0.f, 0.f, false) );
	}
}