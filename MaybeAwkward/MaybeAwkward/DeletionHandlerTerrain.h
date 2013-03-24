#ifndef DeletionHandlerTerrain_h__
#define DeletionHandlerTerrain_h__

#include "DeletionHandler.h"

namespace MA
{
class DeletionHandlerTerrain : public DeletionHandler
{
public:
    bool deletion(Entity &aEntity);
};
}
#endif // DeletionHandlerTerrain_h__
