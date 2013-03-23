#ifndef Controller_h__
#define Controller_h__

namespace MA
{

class MessageReceiver;

class Controller
{
public:
    virtual void update(MessageReceiver &aReceiver float dt) =0;
};

}
#endif // Controller_h__
