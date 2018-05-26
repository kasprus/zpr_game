#ifndef GAMEOVERMESSAGE_H
#define GAMEOVERMESSAGE_H

#include "message.h"

namespace Communication {

class Message;
class TranslatorToArray;


class GameOverMessage : public Message
{
public:
    GameOverMessage(int winner);
    virtual int getHeader() const;
    virtual void accept(const TranslatorToArray &translator);
    int getWinner() const;
    virtual ~GameOverMessage();
private:
    int winner;
};

}

#endif // GAMEOVERMESSAGE_H
