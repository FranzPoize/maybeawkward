
#include "GameLogic.h"
#include <map>
#include <stdint.h>

namespace MA {

static uint64_t key(Family f1, Family f2) {
    return (uint64_t)f1 + (uint64_t) f2 << 32;
}

CollisionRule& GameLogic::onBoxCollision(Family f1, Family f2)
{
    CollisionRule& c = _collisionRules[key(f1, f2)];
    c._f1 = f1;
    c._f2 = f2;
}

void GameLogic::update(float dt)
{
    CollisionRuleMap::iterator it = _collisionRules.begin(); 
    CollisionRuleMap::iterator stop = _collisionRules.end();

    while (it != stop) {
        EntityPair pair;

        std::list<CollisionCallback*>::iterator it2 = it->second._callbacks.begin();
        std::list<CollisionCallback*>::iterator stop2 = it->second._callbacks.end();
        while (it2 != stop2) {
            (*it2)->call(pair, dt);
            ++it2;
        }
        ++it;
    }
}

CollisionRule::~CollisionRule() {
    std::list<CollisionCallback*>::iterator it = _callbacks.begin();
    std::list<CollisionCallback*>::iterator stop = _callbacks.end();
    while (it != stop) {
        delete *it;
    }
}


} // namespace
