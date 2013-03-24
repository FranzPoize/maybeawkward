#ifndef DeletionHandlerNull_h__
#define DeletionHandlerNull_h__

#include "DeletionHandler.h"

namespace MA
{
class DeletionHandlerNull : public DeletionHandler
{
public:
    bool deletion(Entity &aEntity)
    {
        return true;
    }
};
}
#endif // DeletionHandlerNull_h__
