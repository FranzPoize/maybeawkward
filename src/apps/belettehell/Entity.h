
#ifndef Entity_h__
#define Entity_h__

#include "AABB.h"
#include "Physics.h"
#include "MessageVisitor.h"
#include "MessageReceiver.h"
#include "AbstractMessage.h"
#include "constants.h"
#include "QuadTreeProxy.h"

#include <assert.h>
#include <memory>
#include <stdio.h>
#include <deque>
#include <map>
#include <cmath>
#include <string>

namespace MA
{

class Controller;
class Drawer;
class AbstractMessage;
class MoveMessage;
class AttackMessage;
class Attacker;
class AnimationMessage;
class DeletionHandler;
class SpeedMessage;
class Animator;

enum Family {
    ENEMY,
    PLAYER,
    FRIEND,
    ITEM,
    ENEMY_BULLET,
    FRIEND_BULLET,
    TERRAIN,
};

enum AnimState {
    NO_CHANGE,
    IDLE,
    WALKING,
    JUMPING_UP,
    JUMPING_DOWN,
};

const char* animEnumToNounoursStr(AnimState);

typedef std::vector<Family> FamilyVector;

class Entity : public MessageVisitor, public MessageReceiver
{
public:
    //Entity(std::shared_ptr<Controller> aController);
    Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer);
    ~Entity();

    void setAttacker(std::shared_ptr<Attacker> aAttacker)
    {
        mAttacker = aAttacker;
    }

    void setDeletionHandler(std::shared_ptr<DeletionHandler> aDeletionHandler)
    {
        mDeletionHandler = aDeletionHandler;
    }

    void setAnimator(std::shared_ptr<Animator> aAnimator)
    {
        mAnimator = aAnimator;
    }

	void setCameraFactor(float aCameraFactor)
	{
		mCameraFactor = aCameraFactor;
	}

	float cameraFactor() const
	{
		return mCameraFactor;
	}

    bool update(float dt);
    void draw();

    void move(float dt, float aXInput, bool aJump);

    const double x() const
    {
		return mPosition.x;
    }

    const double y() const
    {
		return mPosition.y;
    }

    const float angle() const
    {
        return mPhysicalObject->angle();
    }

    void receiveMessage(std::shared_ptr<AbstractMessage> aInputMessage)
    {
        mMessageBox.push_back(aInputMessage);
    }

    void setPhysicsID(PhysicsID id) {
        assert(mPhysics.type == PHYSICS_INVALID || 
               id.type == PHYSICS_INVALID);
        mPhysics = id;
    }

    PhysicsID physicsID() const {
        return mPhysics;
    }

    std::vector<Family>& families() { return mFamilies; }

    // To be overloaded in derived class (will cause name hiding problems...)
    void visit(AbstractMessage *aVisitedNode, const VisitInfo &info);

    void addChild(std::shared_ptr<Entity> aEntity, int aOrder)
    {
        mChildEntities.insert(ChildPair(aOrder, aEntity));
    }

    void markForDeletion(bool aMarkedForDeletion) {
        mMarkedForDeletion = aMarkedForDeletion;
    }


	bool isMarkedForDeletion()
	{
		return mMarkedForDeletion;
	}

    void setDrawer(std::shared_ptr<Drawer> aDrawer)
    {
        mDrawer = aDrawer;
    }

    bool isGrounded() {
        return x() > PHYSICS_Y_LIMIT - 5;
    }

    bool isGoingUp() {
        return mPhysicalObject->vy() < 0.0f;
    }

    bool isGoingDown() {
        return mPhysicalObject->vy() > 0.0f;
    }

    bool isWalkingRight() {
        return mPhysicalObject->vx() > 0.0f &&
               isGrounded();
    }

    bool isWalkingLeft() {
        return mPhysicalObject->vx() < 0.0f &&
               isGrounded();
    }

    AnimState checkStateChange() {
        if (!mPhysicalObject.get()) return NO_CHANGE;
        AnimState state = NO_CHANGE;
        if (isGoingUp()) {
            state = JUMPING_UP;
        }
        if (isGoingDown()) {
            state = JUMPING_DOWN;
        }

        if (isGrounded() && fabs(mPhysicalObject->vx()) < 0.1f) {
            state = IDLE;
        }
        if (isGrounded() && fabs(mPhysicalObject->vx()) > 0.1f) {
            state = WALKING;
        }
        if (state != NO_CHANGE && state != mState) {
            mState = state;
            return mState;
        } return NO_CHANGE;
    }

    std::string& name() {
        return mName;
    }

    void setPosition(double x, double y)
    {
		mPosition.x = x;
		mPosition.y = y;
		mBoundingBox->setPosition(x, y);
    }

	void setY(double y)
	{
		mPosition.y = y;
		mBoundingBox->setPosition(x(), y);
	}

	void setX(double x)
	{
		mPosition.x = x;
		mBoundingBox->setPosition(x, y());
	}

	void translate(double x, double y)
	{
		mPosition += CL_Vec2d(x, y);
		mBoundingBox->setPosition(mPosition.x, mPosition.y);
	}

	//void setBoundingBox(CL_Vec2d aBoxCenter, double aBoxHalfWidth, double aBoxHalfHeight)
	//{
	//	mBoundingBox.reset(new AABB(aBoxCenter, aBoxHalfWidth, aBoxHalfHeight));
	//}

	void setBoundingBox(double aBoxHalfWidth, double aBoxHalfHeight)
	{
		mBoundingBox.reset(new AABB(mPosition+CL_Vec2d(aBoxHalfWidth, -aBoxHalfHeight),
									aBoxHalfWidth,
									aBoxHalfHeight,
									ORIGIN));
	}

	const AABB& getBoundingBox()
	{
		return *mBoundingBox;
	}

	const AABB& getBoundingBox() const
	{
		return *mBoundingBox;
	}


	void buildPhysicalObject(PhysicsType aType, const PhysicsMaterial* params);
	PhysicalObject * const getPhysicalObject()
	{
		return mPhysicalObject.get();
	}

	BHQuadTree *getQuadTree()
	{
		return mQuadTreeBackPtr;
	}

	void setQuadTree(BHQuadTree *aQuadTreeBackPtr)
	{
		mQuadTreeBackPtr = aQuadTreeBackPtr;
	}


private:
    void visit(MoveMessage *aMessage, const VisitInfo &info);
    void visit(AttackMessage *aMessage, const VisitInfo &info);
	void visit(AnimationMessage *aMessage,const VisitInfo &info);
	void visit(SpeedMessage *aSpeedMessage,const VisitInfo &info);


private:
    typedef std::deque<std::shared_ptr<AbstractMessage> > MessageBoxType;
    typedef MessageBoxType::iterator MessageBoxIterator;

	CL_Vec2d mPosition;
	std::unique_ptr<AABB> mBoundingBox;
	std::unique_ptr<PhysicalObject> mPhysicalObject;

    MessageBoxType mMessageBox;
    std::shared_ptr<Controller> mController;
    std::shared_ptr<Drawer> mDrawer;
    std::shared_ptr<Attacker> mAttacker;
    std::shared_ptr<Animator> mAnimator;
    std::shared_ptr<DeletionHandler> mDeletionHandler;
    PhysicsID mPhysics;
    std::vector<Family> mFamilies;

    // (order, entity) order : of drawing, negative before parent, positive after
    typedef std::map<int, std::shared_ptr<Entity> > ChildrenMap;
    typedef std::pair<int, std::shared_ptr<Entity> > ChildPair;
    typedef ChildrenMap::iterator ChildIterator;
    ChildrenMap mChildEntities;
    bool mMarkedForDeletion;
    AnimState mState;
	float mCameraFactor;
    std::string mName;
	BHQuadTree *mQuadTreeBackPtr;
	
};

}

#endif // Entity_h__
