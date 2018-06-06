#ifndef POINTMESSAGE_H
#define POINTMESSAGE_H

#include <vector>

#include "point.h"
#include "message.h"

namespace Communication {

class TranslatorToArray;
class MessageVisitor;
class Message;

/**
 * @brief The PointMessage class provides information about points on a game board
 */
class PointMessage : public Message
{
public:
    static constexpr const int messageItemSize = 37;
    PointMessage();
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    int getCapacity() const;
    std::vector<GamePlay::Point> getPoints() const;
    bool addPoint(const GamePlay::Point& p);
    virtual ~PointMessage();
private:
    std::vector<GamePlay::Point>points;
};

}

#endif // POINTMESSAGE_H
