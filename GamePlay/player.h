#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"
#include "board.h"

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
    void cancelRotatingLeft();
    void cancelRotatingRight();
    Point getPoint(long turn) const;
    bool isActive() const;
    void setInactive();
    void reset();
private:
    const int id;
    double x;
    double y;
    double angle;
    bool rotatingLeft;
    bool rotatingRight;
    bool active;
};

}
#endif // PLAYER_H
