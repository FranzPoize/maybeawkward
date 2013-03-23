
#include "GameLogic.h"
#include "Closure.h"
#include "Entity.h"

namespace MA {

void on_friend_enemy_bullet_collision(EntityPair& entities, float dt)
{
    printf("[FRIEND,ENEMY_BULLET] Collisioooooooooooon\n");
    // entities.e1 is the first entity invloved in the collision
    // entities.e2 is the second entity invloved in the collision
}

void on_friend_enemy_collision(EntityPair& entities, float dt)
{
    printf("[FRIEND,ENEMY] Collisioooooooooooon\n");
}

void init_gameplay(GameLogic* logic) {

    logic->onBoxCollision(FRIEND, ENEMY_BULLET).add(
        closure<EntityPair>(&on_friend_enemy_bullet_collision)
    );
    logic->onBoxCollision(FRIEND, ENEMY).add(
        closure<EntityPair>(&on_friend_enemy_collision)
    );
    logic->onBoxCollision(FRIEND, FRIEND).add(
        closure<EntityPair>(&on_friend_enemy_collision)
    );

}

} // namespace

