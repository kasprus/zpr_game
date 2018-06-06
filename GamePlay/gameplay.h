#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {

/**
 * @brief The GamePlay class contains constants representing game parameters
 */
class GamePlay
{

public:
    constexpr static long turnInterval = 20;
    constexpr static double slowSpeedPerTurn = 0.0020;
    constexpr static double defaultSpeedPerTurn = 0.0030;
    constexpr static double fastSpeedPerTurn = 0.0040;
    constexpr static double defaultAngle = 0.075;
    constexpr static double defaultRadius = 0.008;
    constexpr static double bigRadius = 0.015;
    constexpr static double smallRadius = 0.005;
    constexpr static int numberOfInactiveCollisionTurns = 16;
    constexpr static int secondsOfGameDelay = 3;
    constexpr static int maximumNumberOfPlayers = 6;
    constexpr static int intervalBetweenBonusManagement = 200;
    constexpr static int intervalWithInvisiblePoint = 0b110000;
private:
    GamePlay();
};

}

#endif // GAMEPLAY_H
