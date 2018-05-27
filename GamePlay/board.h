#ifndef BOARD_H
#define BOARD_H

#include <QMultiMap>

#include "point.h"
#include "gamemode.h"

namespace GamePlay {
class GameMode;
enum class Mode;

class Board
{
public:
    constexpr static const double dimensionX = 1.0;
    constexpr static const double dimensionY = 1.0;
    constexpr static const double bonusSize = 0.05;

    Board();
    void registerPoint(Point p);
    void registerBonus(Bonus b);
    void removeBonus(int mode);
    void eraseBoard();
    bool checkCollision(const Point& p) const;
    Bonus checkBonusCollision(const Point& p) const;
private:
    QMultiMap<double, Point> pointsSet;
    QMultiMap<int, Bonus> bonusSet;

};

}

#endif // BOARD_H
