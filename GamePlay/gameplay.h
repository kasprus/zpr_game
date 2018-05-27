#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {



class GamePlay
{

public:
    static const long turnInterval = 20;
    constexpr static const double slowSpeedPerTurn = 0.0020;
    constexpr static const double defaultSpeedPerTurn = 0.0030;
    constexpr static const double fastSpeedPerTurn = 0.0040;
    constexpr static const double defaultAngle = 0.075;

    constexpr static const double defaultRadius = 0.008;
    constexpr static const double bigRadius = 0.015;
    constexpr static const double smallRadius = 0.005;
    constexpr static const int numberOfInactiveCollisionTurns = 16;

    constexpr static const int secondsOfGameDelay = 3;
    constexpr static const int maximumNumberOfPlayers = 6;
private:
    GamePlay();
};

}

#endif // GAMEPLAY_H
