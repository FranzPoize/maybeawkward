
#include "Physics.h"
#include "Entity.h"
#include "constants.h"
#include <assert.h>

#include <stdio.h>

namespace MA {

static PhysicsSystem* _system = new PhysicsSystem();

PhysicalObject::PhysicalObject(Entity *const aEntity, const PhysicsMaterial* m) :
	/* _x(0), _y(0),*/ _dx(0),
	_dy(0),
	_angle(0),
	mBackEntity(aEntity)
{
    if (m)
	{
        _material = *m;
		mBackEntity->setBoundingBox(m->width/2, m->height/2);
    }
	else
	{
		mBackEntity->setBoundingBox(0., 0.);
	}
}

void BoxPhysicalObject::applyVelocity(float dt)
{
    mBackEntity->translate(dt * _dx, dt * _dy);
    _dx = _dx / _material.airFriction;
}

void BoxPhysicalObject::applyForce(float fx, float fy)
{
	_dx += fx / _material.mass;
	_dy += fy / _material.mass;
}

void BoxPhysicalObject::checkFloorCollision()
{
    if (mBackEntity->y() > PHYSICS_Y_LIMIT) 
	{
        if (mBackEntity->y() > PHYSICS_Y_LIMIT - 3) 
		{
            _dx = _dx * _material.groundFriction;
        }
        mBackEntity->setY(PHYSICS_Y_LIMIT);
        _dy = - _dy * 0.5f;
    }
}

void BoxPhysicalObject::applyVelocity(Slice<BoxPhysicalObject> objects, float dt)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        it->mBackEntity->translate(dt * it->_dx, dt * it->_dy);
        it->_dx = it->_dx / it->_material.airFriction;
        ++it;
    }
}


void BoxPhysicalObject::applyForce(Slice<BoxPhysicalObject> objects, float fx, float fy)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (it != objects.end()) {
        it->_dx += fx / it->_material.mass;
        it->_dy += fy / it->_material.mass;
        ++it;
    }
}

void BoxPhysicalObject::checkFloorCollision(Slice<BoxPhysicalObject> objects)
{
    Slice<BoxPhysicalObject>::iterator it = objects.begin();
    while (!objects.empty()) {
        if (objects.front().mBackEntity->y() > PHYSICS_Y_LIMIT) {
            if (objects.front().mBackEntity->y() > PHYSICS_Y_LIMIT - 3) {
                objects.front()._dx = objects.front()._dx * objects.front()._material.groundFriction;
            }
            objects.front().mBackEntity->setY(PHYSICS_Y_LIMIT);
            objects.front()._dy = - objects.front()._dy * 0.5f;
        }
        objects.shrinkLeft();
    }
}


void BoxPhysicalObject::update(float dt)
{
	applyForce(GRAVITY_X, GRAVITY_Y);
	applyVelocity(dt);
	checkFloorCollision();
}

void BoxPhysicalObjectNoGravity::update(float dt)
{
	applyVelocity(dt);
}

void PhysicsSystem::init()
{
    _system->mPhysicsCount = 0;
    _system->_boxesWithGravity.reserve(1024);
}

void PhysicsSystem::update(float dt)
{
    // apply speed to position
    if (_system->_boxesNoGravity.size() > 0) {
        BoxPhysicalObject::applyVelocity(slice(&_system->_boxesNoGravity[0],
                                                _system->_boxesNoGravity.size()),
                                         dt);
    }
    if (_system->_boxesWithGravity.size() > 0) {

    // gravity
		BoxPhysicalObject::applyForce(slice(&_system->_boxesWithGravity[0],
				                              _system->_boxesWithGravity.size()),
					                  GRAVITY_X,
						              GRAVITY_Y);
        BoxPhysicalObject::applyVelocity(slice(&_system->_boxesWithGravity[0],
                                                _system->_boxesWithGravity.size()),
                                         dt);        
        // make sure objects stay in the scene
        BoxPhysicalObject::checkFloorCollision(slice(&_system->_boxesWithGravity[0],
                                                _system->_boxesWithGravity.size()));
    }
}

void PhysicsSystem::addEntity(Entity &aEntity, PhysicsType type, const PhysicsMaterial* params)
{
//    switch (type) {
//        case PHYSICS_BOX: {
//            _system->_boxesNoGravity.push_back(BoxPhysicalObject(&aEntity, params));
//            aEntity.setPhysicsID(PhysicsID(_system->_boxesNoGravity.size()-1, type));
//            break;
//        }
//        case PHYSICS_BOX_GRAVITY: {
//            _system->_boxesWithGravity.push_back(BoxPhysicalObject(&aEntity, params));
//            aEntity.setPhysicsID(PhysicsID(_system->_boxesWithGravity.size()-1, type));
//            break;    
//        }
//        default: return;
//    }
//    _system->mPhysicsCount++;
//    //printf("num of physical objetcs: %i\n", _system->mPhysicsCount);

	aEntity.buildPhysicalObject(type, params);
}

void PhysicsSystem::removeEntity(Entity &aEntity)
{
/* that's crap
    PhysicsID id = aEntity.physicsID();
    std::vector<BoxPhysicalObject>* container = nullptr;
    switch (id.type) {
        case PHYSICS_BOX: container = &_system->_boxesNoGravity; break;
        case PHYSICS_BOX_GRAVITY: container = &_system->_boxesNoGravity; break;
        default: assert(false);
    }

    if (container) {
        std::vector<BoxPhysicalObject>::iterator it = container->begin();
        std::vector<BoxPhysicalObject>::iterator stop = container->end();
        bool darnit = false;
        for (int i = 0; i < id.index; ++i) { 
            if (it == stop) darnit = true;
            ++it;
        }
        if (!darnit){
            container->erase(it);
            _system->mPhysicsCount--;
        }
    }
*/
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

//void PhysicsSystem::setPosition(PhysicsID id, float px, float py)
//{
//    PhysicalObject* obj = PhysicsSystem::get(id);
//    obj->_x = px;
//    obj->_y = py;
//}

} // namespace
