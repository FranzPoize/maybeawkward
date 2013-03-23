#ifndef Visitor_h__
#define Visitor_h__

namespace MA
{
class Visitor
{
public:
    virtual void visit(Node *aVisitedNode);
};
}
#endif // Visitor_h__
