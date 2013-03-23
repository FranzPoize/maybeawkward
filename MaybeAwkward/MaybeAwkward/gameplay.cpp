
#include "GameLogic.h"
#include "Closure.h"
#include "Entity.h"

namespace MA {

void on_friend_enemy_bullet_collision(EntityPair& entities, float dt)
{
    printf("[FRIEND,ENEMY_BULLET] Collisioooooooooooon\n");
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

}

} // namespace

