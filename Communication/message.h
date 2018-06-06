#ifndef MESSAGE_H
#define MESSAGE_H

namespace Communication {

class PointMessage;
class TranslatorToArray;
class MessageVisitor;

/**
 * @brief The Message class provides interface for messages
 */
class Message
{
public:
    Message();
    virtual void accept(const MessageVisitor& visitor) = 0;
    virtual int getHeader() const = 0;
    virtual ~Message();
};

}

#endif // MESSAGE_H
