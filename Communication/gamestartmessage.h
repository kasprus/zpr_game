#ifndef GAMESTARTMESSAGE_H
#define GAMESTARTMESSAGE_H

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

/**
 * @brief The GameStartMessage class provides information that game has started and game parameters
 */
class GameStartMessage : public Message {
public:
    GameStartMessage(int nPlayers, int maxScore, int playerNumber);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    int getNumberOfPlayers() const;
    int getMaxScore() const;
    int getPlayerNumber() const;
    virtual ~GameStartMessage();
private:
    int nPlayers;
    int maxScore;
    int playerNumber;
};

}
#endif // GAMESTARTMESSAGE_H
