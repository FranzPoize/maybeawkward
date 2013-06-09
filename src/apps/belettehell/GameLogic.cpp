
#include "GameLogic.h"

#include <stdint.h>
#include <stdio.h>
#include "World.h"
#include "collisions.h"
#include "AABB.h"
#include "constants.h"

#include <QuadTree/BoundingBox.h>

namespace MA {

static uint64_t key(Family f1, Family f2) {
    return (uint64_t)f1 + ((uint64_t) f2 << 32);
}

GameLogic::GameLogic():
	mQuadTree(0,
		AABB(CL_Vec2d(WIN_WIDTH/2, WIN_HEIGHT/2),
			WIN_HEIGHT*CULLING_FACTOR_V,
			WIN_WIDTH*CULLING_FACTOR_H,
			ORIGIN))
{

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
    //printf("GameLogic::update\n\n");
    //CollisionRuleMap::iterator it = _collisionRules.begin(); 
    //CollisionRuleMap::iterator stop = _collisionRules.end();
    CollisionRuleMap::iterator it;
    EntityList& entities = World::instance.everybodyList();

   // while (it != stop)
   // {
        //printf("GameLogic::update - iterating over the rules\n");
        //uint64_t pair_key = key(it->second._f1, it->second._f2);

        EntityList::iterator main_entity_it = entities.begin();
        EntityList::iterator main_entity_stop = entities.end();
		for(;main_entity_it != main_entity_stop;main_entity_it++)
		{
			mQuadTree.insertElement(main_entity_it->get());
		}

        main_entity_it = entities.begin();
		for(;main_entity_it != main_entity_stop;main_entity_it++)
		{
		 	BHQuadTree::ElementsContainer container = mQuadTree.searchNeighbors(**main_entity_it);

            //printf("   GameLogic::update - iterating over the first entity\n");
            BHQuadTree::ElementsContainer::iterator secondary_entity_it = container.begin();
            BHQuadTree::ElementsContainer::iterator secondary_entity_stop = container.end();

            while (secondary_entity_it != secondary_entity_stop)
			{
                const AABB& bb1= (*main_entity_it)->getBoundingBox();
                const AABB& bb2= (*secondary_entity_it)->getBoundingBox();

                if (bb1.isColliding(bb2))
				{
	                FamilyVector::iterator family_it1 = (*main_entity_it)->families().begin();
	                FamilyVector::iterator family_stop1 = (*main_entity_it)->families().end();
	                while (family_it1 != family_stop1) {
	                    //printf("         GameLogic::update - iterating over the first family\n");
	                    FamilyVector::iterator family_it2 = (*secondary_entity_it)->families().begin();
	                    FamilyVector::iterator family_stop2 = (*secondary_entity_it)->families().end();
	                    while (family_it2 != family_stop2) {
	                        if ( (it=_collisionRules.find(key(*family_it1, *family_it2)))!=_collisionRules.end() ) {
	                            //printf("            GameLogic::update - iterating over the second family\n");
			                    CallbackList::iterator callbacks_it = it->second._callbacks.begin();
			                    CallbackList::iterator callbacks_stop = it->second._callbacks.end();
			                    EntityPair pair(&**main_entity_it, &**secondary_entity_it);
			                    //printf("                        GameLogic::update collision found\n");
			                    while (callbacks_it != callbacks_stop)
								{
			                        (*callbacks_it)->call(pair, dt);
			                        ++callbacks_it;
			                    }
	                            break;
	                        }
	                        ++family_it2;
	                    }
	                    ++family_it1;
	                }
                }
                ++secondary_entity_it;
            }
        }
     //   ++it;
    //}

		mQuadTree.clear();
}

} // namespace
