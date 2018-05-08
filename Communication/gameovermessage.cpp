#include "gameovermessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

GameOverMessage::GameOverMessage()
{

}

void GameOverMessage::accept(const TranslatorToArray& translator) {
    translator.visit(*this);
}

int GameOverMessage::getHeader() const {
    return Communication::gameOverMessageHeader;
}

GameOverMessage::~GameOverMessage() {

}

}
