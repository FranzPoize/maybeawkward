#include <memory>
#include "Camera.h"
#include "constants.h"
#include "Entity.h"

using namespace MA;

Camera::Camera(float aCameraXPos):
	mCameraXPos(aCameraXPos)
{
	mFollowedEntity = 0;
}

void Camera::update()
{
	if(mFollowedEntity != 0 && (mFollowedEntity->x()+300.f - mCameraXPos > WIN_WIDTH / 2))
	{
		mCameraXPos = mFollowedEntity->x()+300.f - WIN_WIDTH/2;
	}

}