#ifndef GAMEDELAYMESSAGE_H
#define GAMEDELAYMESSAGE_H



#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

class GameDelayMessage : public Message
{
public:
    GameDelayMessage(int delay);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& visitor);
    int getDelay() const;
    virtual ~GameDelayMessage();
private:
    int delay;
};

}

#endif // GAMEDELAYMESSAGE_H
