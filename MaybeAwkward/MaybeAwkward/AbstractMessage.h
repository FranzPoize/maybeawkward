#ifndef AbstractMessage_h__
#define AbstractMessage_h__

namespace MA
{
struct VisitInfo;
class MessageVisitor;
class AbstractMessage
{
public:
    virtual void getVisited(MessageVisitor &, const VisitInfo &info) =0;

};
}
#endif // AbstractMessage_h__
