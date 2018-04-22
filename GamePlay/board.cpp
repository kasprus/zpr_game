#include "board.h"
#include <algorithm>

namespace GamePlay {

Board::Board()
{

}

void Board::registerPoint(Point p) {
    pointsSet.insertMulti(p.getX(), p);
}

bool Board::checkCollision(const Point& p) const {
    auto lowIt = pointsSet.lowerBound(p.getX() - p.getRadius());
    auto highIt = pointsSet.upperBound(p.getX() + p.getRadius());
    while(lowIt != highIt) {
        if(p.checkCollision(lowIt.value()))return true;
        ++lowIt;
    }
    return false;
}

}
