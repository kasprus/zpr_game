#ifndef GAMEOVERMESSAGE_H
#define GAMEOVERMESSAGE_H

#include "message.h"

namespace Communication {

class Message;
class TranslatorToArray;

/**
 * @brief The GameOverMessage class provides information, that there was game over
 */
class GameOverMessage : public Message
{
public:
    GameOverMessage(int winner);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    int getWinner() const;
    virtual ~GameOverMessage();
private:
    int winner;
};

}

#endif // GAMEOVERMESSAGE_H
