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
    Board();
    void registerPoint(Point p);
    //void addBonus();
    void eraseBoard();
    bool checkCollision(const Point& p) const;
    bool checkBonus(const Point& p) const;
private:
    QMultiMap<double, Point> pointsSet;
    GameMode* gameMode;

};

}

#endif // BOARD_H
