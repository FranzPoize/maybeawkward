#ifndef Visitor_h__
#define Visitor_h__

namespace MA
{
class AbstractMessage;
class MoveMessage;
class AttackMessage;
class AnimationMessage;

struct VisitInfo
{
    float dt;
};

class MessageVisitor
{
public:
    virtual void visit(AbstractMessage *aVisitedNode, const VisitInfo &info) =0;
    
    virtual void visit(AttackMessage *aAttackeMessage, const VisitInfo &info) =0;
    virtual void visit(MoveMessage *aMoveMessage, const VisitInfo &info) =0;

	virtual void visit(AnimationMessage *aAnimationMessage,const VisitInfo &info) =0;
};

}
#endif // Visitor_h__
