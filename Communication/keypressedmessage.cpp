#include "keypressedmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

KeyPressedMessage::KeyPressedMessage(int key) : keyId(key)
{

}

int KeyPressedMessage::getHeader() const {
    return Communication::keyPressedMessageHeader;
}

int KeyPressedMessage::getKeyId() const {
    return keyId;
}

void KeyPressedMessage::accept(const MessageVisitor& translator) {
    translator.visit(*this);
}

KeyPressedMessage::~KeyPressedMessage() {
}


}
