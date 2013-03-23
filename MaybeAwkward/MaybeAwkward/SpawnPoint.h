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
	SpawnPoint(EnemyType aType,float aX, float aY):
		mType(aType),
		x(aX),
		y(aY)
		{}
	EnemyType mType;
	float x;
	float y;
};
}
#endif