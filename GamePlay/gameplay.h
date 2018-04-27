#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {



class GamePlay
{

public:
    static const long turnInterval = 20;
    constexpr static const double defaultSpeedPerTurn = 0.0030;
    constexpr static const double defaultAngle = 0.1;
    constexpr static const double defaultRadius = 0.008;
    constexpr static const double bigRadius = 0.016;
    constexpr static const double smallRadius = 0.005;
    constexpr static const int numberOfInactiveCollisionTurns = 10;
private:
    GamePlay();
};

}

#endif // GAMEPLAY_H
