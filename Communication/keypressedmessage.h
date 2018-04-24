#ifndef KEYPRESSEDMESSAGE_H
#define KEYPRESSEDMESSAGE_H

#include "message.h"

namespace Communication {

class TranslatorToArray;
class Message;

class KeyPressedMessage : public Message
{
public:
    KeyPressedMessage(int key);
    virtual int getHeader() const;
    virtual void accept(const TranslatorToArray& translator);
    int getKeyId() const;
    virtual ~KeyPressedMessage();
private:
    int keyId;
};

}

#endif // KEYPRESSEDMESSAGE_H
