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
	if(mFollowedEntity->x() - mCameraXPos > WIN_WIDTH / 2)
	{
		mCameraXPos = mFollowedEntity->x() - WIN_WIDTH/2;
	}

}