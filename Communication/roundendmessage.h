#ifndef ROUNDENDMESSAGE_H
#define ROUNDENDMESSAGE_H

#include <vector>
#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

class RoundEndMessage : public Message {
public:
    RoundEndMessage(int nPlayers);
    virtual int getHeader() const;
    virtual void accept(const TranslatorToArray& translator);
    std::vector<int> getScore() const;
    int getNumberOfPlayers() const;
    void addScore(int index, int score);
    virtual ~RoundEndMessage();
private:
    std::vector<int> scores;
    int nPlayers;

};

}
#endif // ROUNDENDMESSAGE_H
