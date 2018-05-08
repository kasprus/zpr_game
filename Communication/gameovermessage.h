#ifndef GAMEOVERMESSAGE_H
#define GAMEOVERMESSAGE_H

#include "message.h"

namespace Communication {

class Message;
class TranslatorToArray;


class GameOverMessage : public Message
{
public:
    GameOverMessage();
    virtual int getHeader() const;
    virtual void accept(const TranslatorToArray &translator);
    virtual ~GameOverMessage();
};

}

#endif // GAMEOVERMESSAGE_H
