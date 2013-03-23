#include <memory>
#include "Camera.h"
#include "constants.h"
#include "Entity.h"

using namespace MA;

Camera::Camera(std::shared_ptr<Entity> aFollowedEntity,float aCameraXPos):
	mFollowedEntity(aFollowedEntity),
	mCameraXPos(aCameraXPos)
{
}

void Camera::update()
{
	if(mFollowedEntity->x() - mCameraXPos > WIN_WIDTH / 2)
	{
		mCameraXPos = mFollowedEntity->x();
	}

}