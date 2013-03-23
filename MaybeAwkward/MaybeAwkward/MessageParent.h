#ifndef MessageParent_h__
#define MessageParent_h__

#include "AbstractMessage.h"
#include "MessageVisitor.h"

namespace MA
{
template <class T_derived>
class MessageParent : public AbstractMessage
{
public:
    void getVisited (MessageVisitor &visitor, const VisitInfo &info)
    {
        visitor.visit(static_cast<T_derived*>(this), info);
    }
};
}
#endif // MessageParent_h__
