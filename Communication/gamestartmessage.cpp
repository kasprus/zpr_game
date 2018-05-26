#include "gamestartmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

class TranslatorToArray;
class Message;

GameStartMessage::GameStartMessage(int nPlayers_, int maxScore_, int playerNumber_) : nPlayers(nPlayers_), maxScore(maxScore_), playerNumber(playerNumber_) {

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

int GameStartMessage::getPlayerNumber() const {
    return playerNumber;
}

GameStartMessage::~GameStartMessage() {

}

}
