#include "board.h"
#include "gameplay.h"
#include <algorithm>

namespace GamePlay {

Board::Board()
{

}

void Board::registerPoint(Point p) {
    pointsSet.insertMulti(p.getX(), p);
}

bool Board::checkCollision(const Point& p) const {
    if(p.checkEdgeCollision())return true;
    auto lowIt = pointsSet.lowerBound(p.getX() - GamePlay::bigRadius);
    auto highIt = pointsSet.upperBound(p.getX() + GamePlay::bigRadius);
    while(lowIt != highIt) {
        if(p.checkCollision(lowIt.value()))return true;
        ++lowIt;
    }
    return false;
}

}
