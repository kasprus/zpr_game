#ifndef PLAYER_H
#define PLAYER_H


#include "point.h"
#include "board.h"
#include "gamemode.h"

namespace GamePlay {
class GameMode;
enum class Mode;

/**
 * @brief The Player class represents game player
 */
class Player
{
public:
    Player(int id, double x, double y, double angle);
    Point move(long turn);
    double getX() const;
    double getY() const;
    int getScore() const;
    int getID() const;
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
    void updateMode(const Bonus& bonus);
private:
    const int id;
    int score;
    double x;
    double y;
    double angle;
    double radius;
    double speed;
    bool visible;
    bool squares;
    bool collisionless;
    bool rotatingLeft;
    bool rotatingRight;
    bool active;
    bool reversed;
    void setMode(int mode, int playerID);
    void resetMode(int mode, int playerID);

};

}
#endif // PLAYER_H
