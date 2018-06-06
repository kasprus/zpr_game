#include "gamescoremessage.h"
#include "communication.h"
#include "messagevisitor.h"

namespace Communication {


GameScoreMessage ::GameScoreMessage(int playersCount) : scores(playersCount, 0), playersCount(playersCount)
{

}

GameScoreMessage::~GameScoreMessage() {

}
int GameScoreMessage::getHeader() const {
    return Communication::gameScoreMessageHeader;
}

void GameScoreMessage::accept(const MessageVisitor& visitor) {
    visitor.visit(*this);
}

void GameScoreMessage::addScore(int index, int score) {
    scores.at(index) = score;
}

std::vector<int> GameScoreMessage::getScore() const {
    return scores;
}

int GameScoreMessage::getNumberOfPlayers() const {
    return playersCount;
}

}
