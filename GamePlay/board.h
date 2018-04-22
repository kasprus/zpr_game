#ifndef BOARD_H
#define BOARD_H

#include <QMultiMap>
#include "point.h"

namespace GamePlay {

class Board
{
public:
    constexpr static const double dimensionX = 1.0;
    constexpr static const double dimensionY = 1.0;
    Board();
    void registerPoint(Point p);
    bool checkCollision(const Point& p) const;
private:
    QMultiMap<double, Point> pointsSet;
};

}

#endif // BOARD_H
