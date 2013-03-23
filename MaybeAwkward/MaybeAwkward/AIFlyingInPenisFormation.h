#ifndef AIFlyingInPenisFormation_h__
#define AIFlyingInPenisFormation_h__

#include "Controller.h"

namespace MA
{
class Entity;
class AIFlyingInPenisFormation : public Controller
{
public:
	AIFlyingInPenisFormation();
	void update(Entity &aEntity, float dt);
private:
	float mXSpeed;
};
}
#endif