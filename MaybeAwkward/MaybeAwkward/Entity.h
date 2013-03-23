#ifndef Entity_h__
#define Entity_h__

#include "MessageVisitor.h"
#include "MessageReceiver.h"
#include "AbstractMessage.h"

#include <memory>
#include <deque>

namespace MA
{

class Controller;
class Drawer;
class AbstractMessage;
class MoveMessage;
class AttackMessage;

class Entity : public MessageVisitor, public MessageReceiver
{
public:
    //Entity(std::shared_ptr<Controller> aController);
    Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer);

    void update(float dt);
    void draw();

    void move(float dt, float aXInput, bool aJump);

    const float &x() const
    {
        return mXpos;
    }

    const float &y() const
    {
        return mYpos;
    }

    void receiveMessage(std::shared_ptr<AbstractMessage> aInputMessage)
    {
        mMessageBox.push_back(aInputMessage);
    }

public:
    // To be overloaded in derived class (will cause name hiding problems...)
    void visit(AbstractMessage *aVisitedNode, const VisitInfo &info);

    void visit(MoveMessage *aMessage, const VisitInfo &info);
    void visit(AttackMessage *aMessage, const VisitInfo &info);
private:
    typedef std::deque<std::shared_ptr<AbstractMessage> > MessageBoxType;
    typedef MessageBoxType::iterator MessageBoxIterator;

    MessageBoxType mMessageBox;
    std::shared_ptr<Controller> mController;
    std::shared_ptr<Drawer> mDrawer;

    float mXpos;
    float mYpos;
};

}

#endif // Entity_h__
