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
	AABB(clan::Vec2d aCenter, double aHalfWidth, double aHalfHeight, clan::Origin aOrigin);
	virtual bool isColliding(const AABB& aLeftBB) const ;
	virtual AABB getQuadrant(unsigned int aQuadrantId) const ;
	virtual bool contains(const AABB& aBBox) const ;

	operator clan::Rectd() const
	{
		return clan::Rectd(mCenter.x-mHalfWidth, mCenter.y-mHalfHeight, mCenter.x+mHalfWidth, mCenter.y+mHalfHeight);
	}

	/// \brief : returns x1, y1, x2, y2
	operator clan::Vec4d() const
	{
		return clan::Vec4d(mCenter.x-mHalfWidth, mCenter.y-mHalfHeight, mCenter.x+mHalfWidth, mCenter.y+mHalfHeight);
	}

	void setPosition(double x, double y)
	{
		mCenter.x = x - (mHAlignFactor*mHalfWidth);
		mCenter.y = y - (mVAlignFactor*mHalfHeight);
	}


private:
	int mHAlignFactor;
	int mVAlignFactor;
	clan::Vec2d mCenter;
	double mHalfWidth;
	double mHalfHeight;
};
}

#endif // AABB_h__