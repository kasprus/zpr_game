#ifndef POINT_H
#define POINT_H

namespace GamePlay {

/**
 * @brief The Point class provides implementation of a game point which na be put on the board
 */
class Point
{
public:
    Point(double x, double y, double radius, long turnNumber, int playerNumber, bool visble = false);
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
    bool isVisible() const {
        return visible;
    }
    bool checkCollision(const Point &p) const;
    bool checkEdgeCollision() const;
private:
    const double x;
    const double y;
    const double radius;
    const long turnNumber;
    const int playerId;
    const int visible;
};

}

#endif // POINT_H
