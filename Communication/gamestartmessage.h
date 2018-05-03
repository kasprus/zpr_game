#ifndef GAMESTARTMESSAGE_H
#define GAMESTARTMESSAGE_H

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

class GameStartMessage : public Message {
public:
    GameStartMessage(int nPlayers, int maxScore);
    virtual int getHeader() const;
    virtual void accept(const TranslatorToArray& translator);
    int getNumberOfPlayers() const;
    int getMaxScore() const;
    virtual ~GameStartMessage();
private:
    int nPlayers;
    int maxScore;
};

}
#endif // GAMESTARTMESSAGE_H
