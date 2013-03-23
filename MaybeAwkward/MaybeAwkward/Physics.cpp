
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
    printf("batched apply force \n");

    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        if (it->_y > PHYSICS_Y_LIMIT) {
            it->_y = PHYSICS_Y_LIMIT;
            it->_dy = -it->_dy * 0.5;
            printf("BWIING! \n");
        }
        ++it;
    }
}


void BoxPhysicalObject::update(const Entity &aEntity, float dt)
{

}

void PhysicsSystem::init()
{
    _system->_boxes.reserve(1024);
}

void PhysicsSystem::update(float dt)
{
    BoxPhysicalObject::applyForce(slice(&_system->_boxes[0],
                                         _system->_boxes.size()),
                                  GRAVITY_X,
                                  GRAVITY_Y);
    BoxPhysicalObject::applyVelocity(slice(&_system->_boxes[0],
                                            _system->_boxes.size()),
                                     dt);
    BoxPhysicalObject::checkFloorCollision(slice(&_system->_boxes[0],
                                            _system->_boxes.size()));
}

void PhysicsSystem::addEntity(Entity &aEntity)
{
    _system->_boxes.push_back(BoxPhysicalObject());
    aEntity.setPhysicsID(PhysicsID(_system->_boxes.size()-1, PHYSICS_BOX));
}

void PhysicsSystem::removeEntity(Entity &aEntity)
{

}

PhysicalObject* PhysicsSystem::get(PhysicsID id)
{
    if (id.type == PHYSICS_INVALID) {
        return nullptr;
    }
    return &_system->_boxes[id.index];
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
