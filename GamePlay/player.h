#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"

namespace GamePlay {

class Player
{
public:
    Player(int id, double x, double y, double angle);
    void move();
    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }
    void setRotatingLeft();
    void setRotatingRight();
    void cancelRoatingLeft();
    void cancelRotatingRight();
    Point getPoint(long turn) const;
private:
    const int id;
    double x;
    double y;
    double angle;
    bool rotatingLeft;
    bool rotatingRight;
};

}
#endif // PLAYER_H
