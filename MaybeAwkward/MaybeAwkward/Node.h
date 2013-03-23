#ifndef Node_h__
#define Node_h__

namespace MA
{
class MessageVisitor;
class Node
{
public:
    virtual void getVisited(MessageVisitor &aVisitor) =0;
};
}
#endif // Node_h__
