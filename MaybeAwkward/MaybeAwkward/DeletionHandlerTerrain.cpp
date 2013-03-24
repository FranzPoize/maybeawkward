#include "DeletionHandlerTerrain.h"

#include "World.h"

using namespace MA;

bool DeletionHandlerTerrain::deletion(Entity &aEntity)
{
    World::instance.addTerrain(World::UN);
    return true;
}