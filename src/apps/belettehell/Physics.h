
#ifndef GDP4_PHYSICS_H
#define GDP4_PHYSICS_H

#include "Slice.h"
#include "collisions.h"

#include <vector>

namespace MA {

class Entity;

enum PhysicsType {
    PHYSICS_INVALID,
    PHYSICS_BOX,
    PHYSICS_BOX_GRAVITY
};

struct PhysicsID {
    PhysicsID(int aIndex = 0, char aType = PHYSICS_INVALID)
    : index(aIndex), type(aType) {}
    int index;
    char type;
};

struct PhysicsMaterial {
    PhysicsMaterial(float af = 1.0, float gf = 1.0, float m = 1.0, float w = 0, float h = 0)
    : airFriction(af), groundFriction(gf), mass(m)
    , width(w), height(h) {
        if (mass < 1.0) mass = 1.0;
        if (airFriction < 1.0) airFriction = 1.0;
        if (groundFriction < 1.0) groundFriction = 1.0;
    }
    float airFriction;
    float groundFriction;
    float mass;
    float width;
    float height;
};

class PhysicsSystem;

class PhysicalObject
{
public:
    virtual void update(float dt) = 0;
    virtual void applyForce(float fx, float fy) =0;

    PhysicalObject(Entity *const aEntity, const PhysicsMaterial* m);
		
    virtual ~PhysicalObject() {};
    void setAngle(float a) { _angle = a; }
    void setXVelocity(float vx) { _dx = vx; }
    void setYVelocity(float vy) { _dy = vy; }
    const float getXVelocity() const { return _dx; }
    const float getYVelocity() const { return _dy; }

    //float x() const { return _x; }
    //float y() const { return _y; }
    float vx() const { return _dx; }
    float vy() const { return _dy; }
    float angle() const { return _angle; }
    //virtual Rect boundingRect() {
    //    // default rect
    //    return Rect(x(), y(), 0.0, 0.0);
    //}

    //void setX(float x) {_x=x;}
    //void setY(float y) {_y=y;}
protected:

    // position
    //float _x, _y;
    // velocity
    float _dx, _dy;
    float _angle;
    PhysicsMaterial _material;
    friend class MA::PhysicsSystem;

	//back pointer
	Entity* mBackEntity;
};

class BoxPhysicalObject : public PhysicalObject
{
public:

    BoxPhysicalObject(Entity *const aEntity, const PhysicsMaterial* m)
    : PhysicalObject(aEntity, m) {}

    virtual void update(float dt) override;

	void applyVelocity(float dt);
    virtual void applyForce(float fx, float fy);
    void checkFloorCollision();

    static void applyVelocity(Slice<BoxPhysicalObject> objects, float dt);
    static void applyForce(Slice<BoxPhysicalObject> objects, float fx, float fy);
    static void checkFloorCollision(Slice<BoxPhysicalObject> objects);

    //virtual Rect boundingRect() override {
    //    return Rect(x(), y(), _material.width, _material.height);
    //}

    friend class MA::PhysicsSystem;
protected:
};

class BoxPhysicalObjectNoGravity : public BoxPhysicalObject
{
public:
    BoxPhysicalObjectNoGravity(Entity *const aEntity, const PhysicsMaterial* m)
    : BoxPhysicalObject(aEntity, m) {}

    virtual void update(float dt) override;

    friend class MA::PhysicsSystem;
protected:
};


class PhysicsSystem {
public:
    static void init();
    static void update(float dt); // in seconds
    static void applyForce(PhysicsID id, float fx, float fy);
    //static void setPosition(PhysicsID id, float px, float py);

    static void addEntity(Entity &aEntity, PhysicsType type, const PhysicsMaterial* params = 0);
    static void removeEntity(Entity &aEntity);
    static PhysicalObject* get(PhysicsID id);
private:
    std::vector<BoxPhysicalObject> _boxesWithGravity;
    std::vector<BoxPhysicalObject> _boxesNoGravity;
    int mPhysicsCount;
};

} // namespace

#endif
