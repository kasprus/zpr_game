#ifndef KEYPRESSEDMESSAGE_H
#define KEYPRESSEDMESSAGE_H

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

/**
 * @brief The KeyPressedMessage class provides information that some key was pressed
 */
class KeyPressedMessage : public Message
{
public:
    KeyPressedMessage(int key);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    int getKeyId() const;
    virtual ~KeyPressedMessage();
private:
    int keyId;
};

}

#endif // KEYPRESSEDMESSAGE_H
