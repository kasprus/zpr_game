#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "player.h"
#include "vector"

namespace GamePlay {
class Player;


enum class Mode{
    NORMAL,
    SQUARE, SQUARE_O,
    COLLISIONLESS,
    FAST, FAST_O,
    SLOW, SLOW_O,
    THICK, THICK_O,
    THIN, THIN_O,
    REVERSE
};


class GameMode {
public:

    GameMode();
    void addObserver(Player* obs);
    void setMode(Mode mode, int id);
    void setTimeout(int timeout_);
    Mode getMode() const {
        return currentMode;
    }

    int getPlayer() const {
        return playerID;
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

private:
    Mode currentMode;
    int playerID;
    int timeout;
    double x, y;
    std::vector<Player*> observerPlayers;
    void notifyPlayers();
};

}

#endif // GAMEMODE_H
