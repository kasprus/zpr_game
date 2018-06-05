#include "roundendmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

RoundEndMessage::RoundEndMessage(int nPlayers_) : scores(nPlayers_, 0), nPlayers(nPlayers_) {

}

int RoundEndMessage::getHeader() const {
    return Communication::roundEndMessageHeader;
}

void RoundEndMessage::accept(const TranslatorToArray& translator) {
    translator.visit(*this);
}

void RoundEndMessage::addScore(int index, int score) {
    scores.at(index) = score;
}

std::vector<int> RoundEndMessage::getScore() const {
    return scores;
}
int RoundEndMessage::getNumberOfPlayers() const {
    return nPlayers;
}
RoundEndMessage::~RoundEndMessage() {

}

}
