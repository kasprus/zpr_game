#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {



class GamePlay
{

public:
    static const long turnInterval = 30;
    constexpr static const double defaultSpeedPerTurn = 0.001;
    constexpr static const double defaultAngle = 0.0001;
    constexpr static const double defaultRadius = 0.05;
    GamePlay();
};

}

#endif // GAMEPLAY_H
