#include "message.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "communication.h"
#include "../GamePlay/point.h"

namespace Communication {

PointMessage::PointMessage()
{

}

void PointMessage::accept(const TranslatorToArray& translator) {
    translator.visit(*this);
}

int PointMessage::getCapacity() const {
    int remaining = Communication::messageSize - Communication::headerSize - messageItemSize * points.size();
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

int PointMessage::getHeader() {
    return Communication::Communication::pointMessageHeader;
}

PointMessage::~PointMessage() {

}

}
