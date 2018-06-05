#include "message.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "messagevisitor.h"
#include "communication.h"
#include "point.h"

namespace Communication {

PointMessage::PointMessage()
{

}

void PointMessage::accept(const MessageVisitor& translator) {
    translator.visit(*this);
}

int PointMessage::getCapacity() const {
    int remaining = static_cast<int>(Communication::messageSize - Communication::headerSize - messageItemSize * points.size());
    return remaining / messageItemSize;
}

bool PointMessage::addPoint(const GamePlay::Point &p) {
    if(getCapacity() > 0) {
        points.push_back(p);
        return true;
    }
    return false;
}

std::vector<GamePlay::Point> PointMessage::getPoints() const {
    return points;
}

int PointMessage::getHeader() const{
    return Communication::Communication::pointMessageHeader;
}

PointMessage::~PointMessage() {

}

}
