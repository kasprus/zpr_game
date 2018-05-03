#include "gamestartmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

class TranslatorToArray;
class Message;

GameStartMessage::GameStartMessage(int nPlayers_, int maxScore_) : nPlayers(nPlayers_), maxScore(maxScore_) {

}

int GameStartMessage::getHeader() const {
    return Communication::gameStartMessageHeader;
}

void GameStartMessage::accept(const TranslatorToArray& translator) {
    translator.visit(*this);
}

int GameStartMessage::getMaxScore() const {
    return maxScore;
}

int GameStartMessage::getNumberOfPlayers() const {
    return nPlayers;
}

GameStartMessage::~GameStartMessage() {

}

}
