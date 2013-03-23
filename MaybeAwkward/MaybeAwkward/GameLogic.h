
#ifndef MA_GAMELOGIC_H
#define MA_GAMELOGIC_H

#include "Closure.h"
#include "Entity.h"

namespace MA {

class Entity;

namespace GameLogic {

struct EntityPair {
    Entity* e1;
    Entity* e2;
};

class CollisionRule {
    void add(Closure<EntityPair>& callback);
};

CollisionRule& onBoxCollision(Family f1, Family f2);

} // GameLogic

} // namespace

#endif
