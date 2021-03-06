#ifndef KEYRELEASEDMESSAGE_H
#define KEYRELEASEDMESSAGE_H

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

/**
 * @brief The KeyReleasedMessage class provides information that some key has been released
 */
class KeyReleasedMessage : public Message
{
public:
    KeyReleasedMessage(int key);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    int getKeyId() const;
    virtual ~KeyReleasedMessage();
private:
    int keyId;
};

}

#endif // KEYRELEASEDMESSAGE_H
