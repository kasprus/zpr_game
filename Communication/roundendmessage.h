#ifndef ROUNDENDMESSAGE_H
#define ROUNDENDMESSAGE_H

#include <vector>

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

/**
 * @brief The RoundEndMessage class provides information that round is over
 */
class RoundEndMessage : public Message {
public:
    RoundEndMessage();
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    virtual ~RoundEndMessage();
private:
    std::vector<int> scores;
    int nPlayers;

};

}
#endif // ROUNDENDMESSAGE_H
