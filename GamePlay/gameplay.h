#ifndef GAMEPLAY_H
#define GAMEPLAY_H

namespace GamePlay {



class GamePlay
{

public:
    static const long turnInterval = 20;
    constexpr static const double defaultSpeedPerTurn = 0.00001;
    constexpr static const double defaultAngle = 0.0001;
    constexpr static const double defaultRadius = 0.0001;
    GamePlay();
};

}

#endif // GAMEPLAY_H
