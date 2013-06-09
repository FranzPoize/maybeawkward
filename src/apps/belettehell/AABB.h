#ifndef AABB_h__
#define AABB_h__

#include <QuadTree/BoundingBox.h>
#include <ClanLib/Core/Math/vec2.h>

namespace MA
{
class AABB : public BHQT::BoundingBox<AABB>
{
public:
	AABB(CL_Vec2d aCenter, int aHalfWidth, int aHalfHeight);
	virtual bool isColliding(const AABB& aLeftBB) const ;
	virtual AABB getQuadrant(unsigned int aQuadrantId) const ;
	virtual bool contains(const AABB& aBBox) const ;

private:
	CL_Vec2d mCenter;
	int mHalfWidth;
	int mHalfHeight;
};
}

#endif // AABB_h__