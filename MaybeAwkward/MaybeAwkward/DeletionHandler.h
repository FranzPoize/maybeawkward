#ifndef DeletionHandler_h__
#define DeletionHandler_h__

namespace MA
{

class Entity;

class DeletionHandler
{
public:
    virtual bool deletion(Entity &aEntity) =0;
};
}
#endif // DeletionHandler_h__
