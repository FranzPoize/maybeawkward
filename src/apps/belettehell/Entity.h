
#ifndef Entity_h__
#define Entity_h__

#include "Physics.h"
#include "MessageVisitor.h"
#include "MessageReceiver.h"
#include "AbstractMessage.h"
#include "constants.h"

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

    PhysicalObject *getPhysics()
    {
        return PhysicsSystem::get(mPhysics);
    }

    const PhysicalObject *getPhysics() const
    {
        return PhysicsSystem::get(mPhysics);
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

    const float x() const
    {
        return PhysicsSystem::get(mPhysics)->x();
        printf("get x: %f\n", PhysicsSystem::get(mPhysics)->x());
    }

    const float y() const
    {
        return PhysicsSystem::get(mPhysics)->y();
    }

    const float angle() const
    {
        return PhysicsSystem::get(mPhysics)->angle();
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
        return PhysicsSystem::get(physicsID())->y() > PHYSICS_Y_LIMIT - 5;
    }

    bool isGoingUp() {
        return PhysicsSystem::get(physicsID())->vy() < 0.0f;
    }

    bool isGoingDown() {
        return PhysicsSystem::get(physicsID())->vy() > 0.0f;
    }

    bool isWalkingRight() {
        return PhysicsSystem::get(physicsID())->vx() > 0.0f &&
               isGrounded();
    }

    bool isWalkingLeft() {
        return PhysicsSystem::get(physicsID())->vx() < 0.0f &&
               isGrounded();
    }

    AnimState checkStateChange() {
        PhysicalObject* o = PhysicsSystem::get(physicsID());
        if (!o) return NO_CHANGE;
        AnimState state = NO_CHANGE;
        if (isGoingUp()) {
            state = JUMPING_UP;
        }
        if (isGoingDown()) {
            state = JUMPING_DOWN;
        }

        if (isGrounded() && fabs(o->vx()) < 0.1f) {
            state = IDLE;
        }
        if (isGrounded() && fabs(o->vx()) > 0.1f) {
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

private:
    void visit(MoveMessage *aMessage, const VisitInfo &info);
    void visit(AttackMessage *aMessage, const VisitInfo &info);
	void visit(AnimationMessage *aMessage,const VisitInfo &info);
	void visit(SpeedMessage *aSpeedMessage,const VisitInfo &info);

    void translate(float x, float y)
    {
        PhysicsSystem::get(mPhysics)->setX(x);
        PhysicsSystem::get(mPhysics)->setY(y);
    }

private:
    typedef std::deque<std::shared_ptr<AbstractMessage> > MessageBoxType;
    typedef MessageBoxType::iterator MessageBoxIterator;

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
};

}

#endif // Entity_h__
