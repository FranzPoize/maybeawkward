
#include "GameLogic.h"
#include <stdint.h>
#include <stdio.h>
#include "World.h"
#include "collisions.h"

namespace MA {

static uint64_t key(Family f1, Family f2) {
    return (uint64_t)f1 + (uint64_t) f2 << 32;
}

CollisionRule& GameLogic::onBoxCollision(Family f1, Family f2)
{
    CollisionRule& c = _collisionRules[key(f1, f2)];
    c._f1 = f1;
    c._f2 = f2;

    return c;
}

void GameLogic::update(float dt)
{
    printf("GameLogic::update\n\n");
    CollisionRuleMap::iterator it = _collisionRules.begin(); 
    CollisionRuleMap::iterator stop = _collisionRules.end();
    EntityList& entities = World::instance.everybodyList();

    while (it != stop) {
        printf("GameLogic::update - iterating over the rules\n");
        uint64_t pair_key = key(it->second._f1, it->second._f2);

        EntityList::iterator main_entity_it = entities.begin();
        EntityList::iterator main_entity_stop = entities.end();
        while (main_entity_it != main_entity_stop) {
            printf("   GameLogic::update - iterating over the first entity\n");
            EntityList::iterator secondary_entity_it = entities.begin();
            EntityList::iterator secondary_entity_stop = entities.end();
            while (secondary_entity_it != secondary_entity_stop) {
                printf("      GameLogic::update - iterating over the second entity\n");
                bool families_matched = false;
                FamilyVector::iterator family_it1 = (*main_entity_it)->families().begin();
                FamilyVector::iterator family_stop1 = (*main_entity_it)->families().end();
                while (family_it1 != family_stop1) {
                    printf("         GameLogic::update - iterating over the first family\n");
                    FamilyVector::iterator family_it2 = (*secondary_entity_it)->families().begin();
                    FamilyVector::iterator family_stop2 = (*secondary_entity_it)->families().end();
                    while (family_it2 != family_stop2) {
                        if (key(*family_it1, *family_it2) == pair_key) {
                            printf("            GameLogic::update - iterating over the second family\n");
                            families_matched = true;
                            break;
                        }
                        ++family_it2;
                    }
                    if (families_matched) break;
                    ++family_it1;
                }
                Rect r1 = PhysicsSystem::get((*main_entity_it)->physicsID())->boundingRect();
                Rect r2 = PhysicsSystem::get((*secondary_entity_it)->physicsID())->boundingRect();
                if (families_matched) {
                    if (rectCollision(r1, r2)) {
                        CallbackList::iterator callbacks_it = it->second._callbacks.begin();
                        CallbackList::iterator callbacks_stop = it->second._callbacks.end();
                        EntityPair pair(&**main_entity_it, &**secondary_entity_it);
                        while (callbacks_it != callbacks_stop) {
                            (*callbacks_it)->call(pair, dt);
                            ++callbacks_it;
                        }
                    }
                }
                ++secondary_entity_it;
            }
            ++main_entity_it;
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
