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
    int getScore() const {
        return score;
    }
    void setCoordinatesAndAngle(double x, double y, double angle);
    void addScore(int pts);
    void setRotatingLeft();
    void setRotatingRight();
    void cancelRotatingLeft();
    void cancelRotatingRight();
    Point getPoint(long turn) const;
    bool isActive() const;
    void setActive();
    void setInactive();
    void reset();
private:
    const int id;
    int score;
    double x;
    double y;
    double angle;
    bool rotatingLeft;
    bool rotatingRight;
    bool active;    
};

}
#endif // PLAYER_H
