#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {



class GamePlay
{

public:
    static const long turnInterval = 30;
    constexpr static const double defaultSpeedPerTurn = 0.005;
    constexpr static const double defaultAngle = 0.15;
    constexpr static const double defaultRadius = 0.015;
    GamePlay();
};

}

#endif // GAMEPLAY_H
