#include "AABB.h"

#include "constants.h"

using namespace MA;

AABB::AABB(CL_Vec2d aCenter, double aHalfWidth, double aHalfHeight, CL_Origin aOrigin) :
	mCenter(aCenter),
	mHalfWidth(aHalfWidth),
	mHalfHeight(aHalfHeight)
{
	mHAlignFactor = aOrigin%3 - 1;
	mVAlignFactor = aOrigin/3 - 1;
}

bool AABB::isColliding(const AABB& aLeftBB) const 
{
	CL_Vec2d tmp = mCenter - aLeftBB.mCenter;
	return (abs(tmp.x) <= (mHalfWidth+aLeftBB.mHalfWidth)
			&& abs(tmp.y) <= (mHalfHeight+aLeftBB.mHalfHeight));
}

AABB AABB::getQuadrant(unsigned int aQuadrantId) const
{
	double xMultiplier = aQuadrantId%2 ? 0.5 : -0.5;
	double yMultiplier = aQuadrantId/2 ? 0.5 : -0.5;

	return AABB(
		mCenter + CL_Vec2d(xMultiplier*mHalfWidth, yMultiplier*mHalfHeight),
		mHalfWidth / 2,
		mHalfHeight / 2,
		ORIGIN);
		
}

bool AABB::contains(const AABB& aBBox) const
{
	// todo
	CL_Vec2d difference(mHalfWidth-aBBox.mHalfWidth, mHalfHeight-aBBox.mHalfHeight);
	CL_Vec2d centerDifference(mCenter - aBBox.mCenter);
	centerDifference.x = abs(centerDifference.x);
	centerDifference.y = abs(centerDifference.y);

	return	difference.x >= 0. && difference.y > 0. 
			&&difference.x <= centerDifference.x
			&& difference.y <= centerDifference.y;
}