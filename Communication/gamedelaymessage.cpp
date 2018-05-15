#include "gamedelaymessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

GameDelayMessage::GameDelayMessage(int delay) : delay(delay)
{

}

GameDelayMessage::~GameDelayMessage() {

}

int GameDelayMessage::getHeader() const {
    return Communication::Communication::gameDelayMessageHeader;
}

int GameDelayMessage::getDelay() const {
    return delay;
}

void GameDelayMessage::accept(const TranslatorToArray &translator) {
    translator.visit(*this);
}
}
