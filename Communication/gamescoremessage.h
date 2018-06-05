#ifndef GAMESCOREMESSAGE_H
#define GAMESCOREMESSAGE_H

#include <vector>
#include "message.h"

namespace Communication {


class GameScoreMessage : public Message
{
public:
    GameScoreMessage(int nPlayers);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& visitor);
    virtual ~GameScoreMessage();
    std::vector<int> getScore() const;
    int getNumberOfPlayers() const;
    void addScore(int index, int score);
private:
    std::vector<int> scores;
    int playersCount;
};

}


#endif // GAMESCOREMESSAGE_H
