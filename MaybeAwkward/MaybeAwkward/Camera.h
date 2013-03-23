#ifndef Camera_h__
#define Camera_h__

#include <memory>

namespace MA
{
class Entity;
class Camera
{
public:
	Camera(std::shared_ptr<Entity> aFollowedEntity,float aCameraXPos);
	float pos()
	{
		return mCameraXPos;
	}
	void update();
private:
	float mCameraXPos;
	std::shared_ptr<Entity> mFollowedEntity;
};
}
#endif //Camera_h__