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

void Board::registerBonus(Bonus b) {
    bonusSet.insertMulti(b.getMode(), b);
}

void Board::removeBonus(int mode) {
    bonusSet.remove(mode);
}

void Board::eraseBoard() {
    pointsSet.clear();
    bonusSet.clear();
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

Bonus Board::checkBonusCollision(const Point& p) const {
    for(auto it = bonusSet.begin(); it != bonusSet.end(); ++it) {
        double top = it.value().getY(), left = it.value().getX();
        double bottom = top + bonusSize, right = left + bonusSize;
        double x = p.getX(), y = p.getY();
        if((x - GamePlay::defaultRadius < right) && (x + GamePlay::defaultRadius > left)  &&
                  (y + GamePlay::defaultRadius > top) && (y + GamePlay::defaultRadius < bottom)) {
            Bonus bonus(it.value()); bonus.setActive(p.getPlayerId());
            return bonus;
       }
    }

    return Bonus(-1);

}


}
