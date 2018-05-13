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

void Board::eraseBoard() {
    pointsSet.clear();
}

bool Board::checkCollision(const Point& p) const {
    if(p.checkEdgeCollision())return true;
    if(!p.isVisible()) return false;
    auto lowIt = pointsSet.lowerBound(p.getX() - GamePlay::bigRadius);
    auto highIt = pointsSet.upperBound(p.getX() + GamePlay::bigRadius);
    while(lowIt != highIt) {
        if(p.checkCollision(lowIt.value()))return true;
        ++lowIt;
    }
    return false;
}

bool Board::checkBonus(const Point& p) const {
    double bonX = gameMode->getX(), bonY = gameMode->getY();
    double lowX = p.getX() - GamePlay::bigRadius;
    double highX = p.getX() + GamePlay::bigRadius;
    double lowY = p.getY() - GamePlay::bigRadius;
    double highY = p.getY() + GamePlay::bigRadius;

    if(bonX <= highX  && bonX >= lowX && bonY >=lowY && bonY <= highY )
        return true;
    return true;
}

}
