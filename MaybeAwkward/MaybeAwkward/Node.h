#ifndef Node_h__
#define Node_h__

namespace MA
{
class Visitor;
class Node
{
public:
    virtual void getVisited(Visitor &aVisitor) =0;
};
}
#endif // Node_h__
