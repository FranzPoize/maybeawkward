
#include "Physics.h"
#include "Entity.h"
#include "constants.h"

#include <stdio.h>

namespace MA {

static PhysicsSystem* _system = new PhysicsSystem();

void BoxPhysicalObject::applyVelocity(Slice<BoxPhysicalObject> objects, float dt)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        it->_x += dt * it->_dx;
        it->_y += dt * it->_dy;
        ++it;
    }
}

void BoxPhysicalObject::applyForce(Slice<BoxPhysicalObject> objects, float fx, float fy)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        it->_dx += fx;
        it->_dy += fy;
        ++it;
    }
}

void BoxPhysicalObject::checkFloorCollision(Slice<BoxPhysicalObject> objects)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        if (it->_y > PHYSICS_Y_LIMIT) {
            it->_y = PHYSICS_Y_LIMIT;
            it->_dy = -it->_dy * 0.5;
        }
        ++it;
    }
}


void BoxPhysicalObject::update(const Entity &aEntity, float dt)
{

}

void PhysicsSystem::init()
{
    _system->_boxesWithGravity.reserve(1024);
}

void PhysicsSystem::update(float dt)
{
    // gravity
    BoxPhysicalObject::applyForce(slice(&_system->_boxesWithGravity[0],
                                         _system->_boxesWithGravity.size()),
                                  GRAVITY_X,
                                  GRAVITY_Y);
    // apply speed to position
    BoxPhysicalObject::applyVelocity(slice(&_system->_boxesWithGravity[0],
                                            _system->_boxesWithGravity.size()),
                                     dt);
    BoxPhysicalObject::applyVelocity(slice(&_system->_boxesNoGravity[0],
                                            _system->_boxesNoGravity.size()),
                                     dt);
    // make sure objects stay in the scene
    BoxPhysicalObject::checkFloorCollision(slice(&_system->_boxesWithGravity[0],
                                            _system->_boxesWithGravity.size()));
}

void PhysicsSystem::addEntity(Entity &aEntity, PhysicsType type, PhysicsParams* params)
{
    switch (type) {
        case PHYSICS_BOX: {
            _system->_boxesNoGravity.push_back(BoxPhysicalObject());
            aEntity.setPhysicsID(PhysicsID(_system->_boxesNoGravity.size()-1, type));
            break;
        }
        case PHYSICS_BOX_GRAVITY: {
            _system->_boxesWithGravity.push_back(BoxPhysicalObject());
            aEntity.setPhysicsID(PhysicsID(_system->_boxesWithGravity.size()-1, type));
            break;    
        }
        default: break;
    }
}

void PhysicsSystem::removeEntity(Entity &aEntity)
{

}

PhysicalObject* PhysicsSystem::get(PhysicsID id)
{
    switch (id.type) {
        case PHYSICS_BOX: return &_system->_boxesNoGravity[id.index];
        case PHYSICS_BOX_GRAVITY: return &_system->_boxesWithGravity[id.index];
        default:  return nullptr;
    }
}

void PhysicsSystem::applyForce(PhysicsID id, float fx, float fy)
{
    PhysicalObject* obj = PhysicsSystem::get(id);
    obj->_dx += fx;
    obj->_dy += fy;
}

void PhysicsSystem::setPosition(PhysicsID id, float px, float py)
{
    PhysicalObject* obj = PhysicsSystem::get(id);
    obj->_x += px;
    obj->_y += py;
}

} // namespace
