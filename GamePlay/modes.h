#ifndef MODES_H
#define MODES_H

namespace GamePlay {

class Modes {

public:
    constexpr static int MODESCOUNT = 13;

    constexpr static int LASTGROUPBONUS = 11;
    constexpr static int EMPTY_BONUS = -1;

    constexpr static int FAST = 0;
    constexpr static int FAST_O = 1;
    constexpr static int SLOW = 2;
    constexpr static int SLOW_O = 3;

    constexpr static int THICK = 4;
    constexpr static int THICK_O = 5;
    constexpr static int THIN = 6;
    constexpr static int THIN_O = 7;

    constexpr static int SQUARE = 8;
    constexpr static int SQUARE_O = 9;

    constexpr static int REVERSE = 10;
    constexpr static int REVERSE_O = 11;

    constexpr static int COLLISIONLESS = 12;

    constexpr static int NORMAL = 13;
private:
    Modes();
};

}

#endif // MODES_H
