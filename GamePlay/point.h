#ifndef POINT_H
#define POINT_H

namespace GamePlay {

class Point
{
public:
    Point(double x, double y, double radius, long turnNumber, int playerNumber);
    Point(const Point &p) = default;
    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }
    double getRadius() const {
        return radius;
    }
    long getTurnNumber() const {
        return turnNumber;
    }
    int getPlayerId() const {
        return playerId;
    }
    bool checkCollision(const Point &p) const;
private:
    const double x;
    const double y;
    const double radius;
    const long turnNumber;
    const int playerId;
};

}

#endif // POINT_H
