
#include "GameLogic.h"
#include "Closure.h"
#include "Entity.h"

namespace MA {

void on_friend_enemy_bullet_collision(EntityPair& entities, float dt)
{
    entities.e1->markForDeletion(true);
	entities.e1->getPhysicalObject()->setXVelocity(0.f);
    printf("[FRIEND,ENEMY_BULLET] Collisioooooooooooon\n");
	entities.e1->markForDeletion(true);
    // entities.e1 is the first entity invloved in the collision
    // entities.e2 is the second entity invloved in the collision
}

void on_bullet_enemy_collision(EntityPair& entities, float dt)
{
    entities.e2->markForDeletion(true);
}

void init_gameplay(GameLogic* logic) {

    logic->onBoxCollision(FRIEND, ENEMY).add(
        closure<EntityPair>(&on_friend_enemy_bullet_collision)
    );
    logic->onBoxCollision(FRIEND, ENEMY_BULLET).add(
        closure<EntityPair>(&on_friend_enemy_bullet_collision)
    );

    logic->onBoxCollision(FRIEND_BULLET, ENEMY).add(
        closure<EntityPair>(&on_bullet_enemy_collision)
    );
}

} // namespace

