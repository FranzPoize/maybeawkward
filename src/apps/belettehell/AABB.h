#ifndef AABB_h__
#define AABB_h__

#include <QuadTree/BoundingBox.h>
#include <ClanLib/Core/Math/vec2.h>

#include <ClanLib/Core/Math/rect.h>

namespace MA
{
class Entity;

enum valign : int
{
	TOP = -1,
	CENTERV = 0,
	BOTTOM = 1
};

enum halign : int
{
	LEFT = -1,
	CENTERH = 0,
	RIGHT = 1
};

class AABB : public BHQT::BoundingBox<AABB>
{
	friend class Entity;

public:
	AABB(CL_Vec2d aCenter, double aHalfWidth, double aHalfHeight, CL_Origin aOrigin);
	virtual bool isColliding(const AABB& aLeftBB) const ;
	virtual AABB getQuadrant(unsigned int aQuadrantId) const ;
	virtual bool contains(const AABB& aBBox) const ;

	operator CL_Rectd() const
	{
		return CL_Rectd(mCenter.x-mHalfWidth, mCenter.y-mHalfHeight, mCenter.x+mHalfWidth, mCenter.y+mHalfHeight);
	}

	/// \brief : returns x1, y1, x2, y2
	operator CL_Vec4d() const
	{
		return CL_Vec4d(mCenter.x-mHalfWidth, mCenter.y-mHalfHeight, mCenter.x+mHalfWidth, mCenter.y+mHalfHeight);
	}

	void setPosition(double x, double y)
	{
		mCenter.x = x - (mHAlignFactor*mHalfWidth);
		mCenter.y = y - (mVAlignFactor*mHalfHeight);
	}


private:
	int mHAlignFactor;
	int mVAlignFactor;
	CL_Vec2d mCenter;
	double mHalfWidth;
	double mHalfHeight;
};
}

#endif // AABB_h__