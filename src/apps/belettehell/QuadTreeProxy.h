#include <QuadTree/QuadTree.h>

#include "Entity.h"
#include "AABB.h"
#include "constants.h"

using namespace MA;

typedef BHQT::QuadTree<Entity,AABB,MAX_OBJECTS_QUAD_TREE,MAX_LEVELS_QUAD_TREE> BHQuadTree;