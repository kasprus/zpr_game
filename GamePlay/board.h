#ifndef BOARD_H
#define BOARD_H

#include <QMultiMap>

#include "point.h"
#include "gamemode.h"
#include "bonus.h"

namespace GamePlay {
class GameMode;
enum class Mode;

/**
 * @brief The Board class provides implementation of a game board and methods for managing objects on it
 */
class Board
{
public:
    constexpr static double dimensionX = 1.0;
    constexpr static double dimensionY = 1.0;
    constexpr static double bonusSize = 0.05;

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
