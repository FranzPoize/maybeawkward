#ifndef SpawnPoint_h__
#define SpawnPoint_h__
namespace MA
{
class SpawnPoint
{
public:
	enum EnemyType
	{
		NORMAL
	};
	SpawnPoint(EnemyType aType,float aX, float aY,float aXSpeed, float aYSpeed):
		mType(aType),
		x(aX),
		y(aY),
		xSpeed(aXSpeed),
		ySpeed(aYSpeed)
		{}
	EnemyType mType;
	float x;
	float y;
	float xSpeed;
	float ySpeed;
};
}
#endif