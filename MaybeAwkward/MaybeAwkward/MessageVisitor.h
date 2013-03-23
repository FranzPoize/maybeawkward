#ifndef Visitor_h__
#define Visitor_h__

namespace MA
{
class AbstractMessage;
class MoveMessage;

struct VisitInfo
{
    float dt;
};

class MessageVisitor
{
public:
    virtual void visit(AbstractMessage *aVisitedNode, const VisitInfo &info) =0;
    
    virtual void visit(MoveMessage *aMoveMessage, const VisitInfo &info)
    {
        /// \todo

        //visit(static_cast<AbstractMessage*>(aMoveMessage));
    }
};

}
#endif // Visitor_h__
