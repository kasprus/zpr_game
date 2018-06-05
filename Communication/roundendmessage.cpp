#include "roundendmessage.h"
#include "communication.h"
#include "translatortoarray.h"

namespace Communication {

RoundEndMessage::RoundEndMessage()
{

}

int RoundEndMessage::getHeader() const {
    return Communication::roundEndMessageHeader;
}

void RoundEndMessage::accept(const MessageVisitor& translator) {
    translator.visit(*this);
}

RoundEndMessage::~RoundEndMessage() {

}

}
