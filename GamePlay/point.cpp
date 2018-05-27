#include "point.h"
#include "board.h"
#include "gameplay.h"

namespace GamePlay {

Point::Point(double x, double y, double radius, long turnNumber, int playerNumber, bool visible) : x(x), y(y), radius(radius), turnNumber(turnNumber), playerId(playerNumber), visible(visible)
{
}

bool Point::checkCollision(const Point &p) const {
    if(!p.isVisible() || !this->isVisible())return false;
    long turnDifference = p.turnNumber - turnNumber;
    if(turnDifference < 0)turnDifference = -turnDifference;
    if(p.playerId == playerId && turnDifference < GamePlay::numberOfInactiveCollisionTurns) return false;
    double a = getX() - p.getX();
    a *= a;
    double b = getY() - p.getY();
    b *= b;
    if(a + b < (getRadius() + p.getRadius()) * (getRadius() + p.getRadius()))return true;
    return false;
}

bool Point::checkEdgeCollision() const {
    if(x - radius < 0 || x + radius > Board::dimensionX)return true;
    if(y - radius < 0 || y + radius > Board::dimensionY)return true;
    return false;
}

}
