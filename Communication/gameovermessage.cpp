#include "gameovermessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

GameOverMessage::GameOverMessage(int winner) : winner(winner)
{

}

void GameOverMessage::accept(const MessageVisitor& translator) {
    translator.visit(*this);
}

int GameOverMessage::getHeader() const {
    return Communication::gameOverMessageHeader;
}

int GameOverMessage::getWinner() const {
    return winner;
}

GameOverMessage::~GameOverMessage() {

}

}
