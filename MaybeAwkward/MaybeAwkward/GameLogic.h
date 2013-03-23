
#ifndef MA_GAMELOGIC_H
#define MA_GAMELOGIC_H

#include "Closure.h"
#include "Entity.h"
#include "World.h"

#include <map>
#include <list>

namespace MA {

class Entity;


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

typedef std::map<uint64_t, CollisionRule> CollisionRuleMap;

class GameLogic {
public:
    GameLogic(std::shared_ptr<MA::World> w) : _world(w) {}

    CollisionRule& onBoxCollision(Family f1, Family f2);

    void update(float dt);
private:
    CollisionRuleMap _collisionRules;
    std::shared_ptr<MA::World> _world;
};


} // namespace

#endif
