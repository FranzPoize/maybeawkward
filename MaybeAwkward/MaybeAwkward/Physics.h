
#ifndef GDP4_PHYSICS_H
#define GDP4_PHYSICS_H

#include "Slice.h"
#include <vector>

namespace MA {

class Entity;

enum {
    PHYSICS_INVALID = 0,
    PHYSICS_BOX = 1
};

struct PhysicsID {
    PhysicsID(int aIndex = 0, char aType = PHYSICS_INVALID)
    : index(aIndex), type(aType) {}
    int index;
    char type;
};

class PhysicsSystem;

class PhysicalObject
{
public:
    virtual void update(const Entity &aEntity, float dt) = 0;

    PhysicalObject()
    : _x(0), _y(0), _dx(0), _dy(0) {}

    virtual ~PhysicalObject() {};

    float x() { return _x; }
    float y() { return _y; }

    // position
    float _x, _y;
    // velocity
    float _dx, _dy;
    friend class MA::PhysicsSystem;
};

class BoxPhysicalObject : public PhysicalObject
{
public:
    virtual void update(const Entity &aEntity, float dt) override;

    static void applyVelocity(Slice<BoxPhysicalObject> objects, float dt);
    static void applyForce(Slice<BoxPhysicalObject> objects, float fx, float fy);
    static void checkFloorCollision(Slice<BoxPhysicalObject> objects);

    friend class MA::PhysicsSystem;
protected:
};



class PhysicsSystem {
public:
    static void init();
    static void update(float dt); // in seconds
    static void applyForce(PhysicsID id, float fx, float fy);
    static void setPosition(PhysicsID id, float px, float py);

    static void addEntity(Entity &aEntity);
    static void removeEntity(Entity &aEntity);
    static PhysicalObject* get(PhysicsID id);
private:
    std::vector<BoxPhysicalObject> _boxes;
};

} // namespace

#endif
