#include "point.h"

namespace GamePlay {

Point::Point(double x, double y, double radius, long turnNumber, int playerNumber) : x(x), y(y), radius(radius), turnNumber(turnNumber), playerId(playerNumber)
{
}

bool Point::checkCollision(const Point &p) const{
    double a = getX() - p.getX();
    a *= a;
    double b = getY() - p.getY();
    b *= b;
    if(a + b <= (getRadius() + p.getRadius()) * (getRadius() + p.getRadius()))return true;
    return false;
}

}

