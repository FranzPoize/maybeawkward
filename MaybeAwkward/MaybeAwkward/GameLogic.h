
#ifndef MA_GAMELOGIC_H
#define MA_GAMELOGIC_H

#include "Closure.h"
#include "Entity.h"

#include <map>
#include <list>

namespace MA {

class Entity;

struct EntityPair {
    EntityPair(Entity* aE1, Entity* aE2)
    : e1(aE1), e2(aE2)
    {}

    Entity* e1;
    Entity* e2;
};

typedef Closure<EntityPair> CollisionCallback;
typedef std::list<CollisionCallback*> CallbackList;

struct CollisionRule {
    void add(CollisionCallback* callback) {
        _callbacks.push_front(callback);
    }

    std::list<CollisionCallback*> _callbacks;
    Family _f1;
    Family _f2;
};

typedef std::map<uint64_t, CollisionRule> CollisionRuleMap;

class GameLogic {
public:
    CollisionRule& onBoxCollision(Family f1, Family f2);

    void update(float dt);
private:
    CollisionRuleMap _collisionRules;
};


void init_gameplay(GameLogic* logic);


} // namespace

#endif
