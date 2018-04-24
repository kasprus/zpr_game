#include "keyreleasedmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

KeyReleasedMessage::KeyReleasedMessage(int key) :keyId(key)
{

}

int KeyReleasedMessage::getHeader() const {
    return Communication::keyReleasedMessageHeader;
}

int KeyReleasedMessage::getKeyId() const {
    return keyId;
}

void KeyReleasedMessage::accept(const TranslatorToArray &translator) {
    translator.visit(*this);
}

KeyReleasedMessage::~KeyReleasedMessage() {
}

}
