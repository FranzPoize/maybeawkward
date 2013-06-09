#ifndef Camera_h__
#define Camera_h__

#include <memory>

namespace MA
{
class Entity;
class Camera
{
public:
	Camera(float aCameraXPos);
	float pos()
	{
		return mCameraXPos;
	}

	void setPos(float aCameraXPos)
	{
		mCameraXPos = aCameraXPos;
	}
	void followEntity(std::shared_ptr<Entity> aFollowedEntity)
	{
		mFollowedEntity = aFollowedEntity;
	}
	void update();
private:
	float mCameraXPos;
	std::shared_ptr<Entity> mFollowedEntity;
};
}
#endif //Camera_h__