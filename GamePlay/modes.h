#ifndef MODES_H
#define MODES_H

namespace GamePlay {

class Modes {

public:
    constexpr const static int MODESCOUNT = 12;


    constexpr const static int FAST = 0;
    constexpr const static int FAST_O = 1;
    constexpr const static int SLOW = 2;
    constexpr const static int SLOW_O = 3;
    constexpr const static int THICK = 4;
    constexpr const static int THICK_O = 5;
    constexpr const static int THIN = 6;
    constexpr const static int THIN_O = 7;
    constexpr const static int SQUARE = 8;
    constexpr const static int SQUARE_O = 9;
    constexpr const static int REVERSE = 10;
    constexpr const static int COLLISIONLESS = 11;

    constexpr const static int NORMAL = 12;
private:
    Modes();
};

}

#endif // MODES_H
