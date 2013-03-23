
#ifndef MA_GAMELOGIC_H
#define MA_GAMELOGIC_H

#include "Closure.h"
#include "Entity.h"

#include <list>

namespace MA {

class Entity;

namespace GameLogic {

struct EntityPair {
    Entity* e1;
    Entity* e2;
};

typedef Closure<EntityPair> CollisionCallback;
struct CollisionRule {
    void add(CollisionCallback* callback) {
        _callbacks.push_front(callback);
    }
    ~CollisionRule();

    std::list<CollisionCallback*> _callbacks;
    Family _f1;
    Family _f2;
};

CollisionRule& onBoxCollision(Family f1, Family f2);

void update(float dt);

} // GameLogic

} // namespace

#endif
