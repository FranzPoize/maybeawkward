#ifndef BoundingBox_h__
#define BoundingBox_h__

namespace BHQT
{

	/// \todo : move to a common ancestor instead of crtp
	/// \brief Interface for collision detection service.
template <class T>
class BoundingBox
{
public:
	virtual bool isColliding(const T& aLeftBB) const =0;
	virtual T getQuadrant(unsigned int aQuadrantId) const =0;
	virtual bool contains(const T& aBBox) const =0;
};
}
#endif // BoundingBox_h__
