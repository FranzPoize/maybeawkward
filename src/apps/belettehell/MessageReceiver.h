#ifndef MessageReceiver_h__
#define MessageReceiver_h__

#include <memory>

namespace MA
{
class AbstractMessage;

class MessageReceiver
{
public:
    virtual void receiveMessage(std::shared_ptr<AbstractMessage> aInputMessage) =0;
};
}
#endif // MessageReceiver_h__
