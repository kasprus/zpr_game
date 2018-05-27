#include "bonus.h"

namespace GamePlay {

Bonus::Bonus(int mode, int playerID, std::chrono::system_clock::time_point timeout, double x, double y) : mode(mode), playerID(playerID), active(false), timeout(timeout), x(x), y(y)
{
}

Bonus::Bonus(const Bonus& bonus) : Bonus(bonus.getMode(), bonus.getPlayerID() , bonus.getTimeout(), bonus.getX(), bonus.getY())
{
}

int Bonus::getMode() const {
    return mode;
}
int Bonus::getPlayerID() const {
    return playerID;
}
double Bonus::getX() const {
    return x;
}
double Bonus::getY() const {
    return y;
}
std::chrono::system_clock::time_point Bonus::getTimeout() const {
    return timeout;
}

bool Bonus::isActive() const {
    return active;
}

void Bonus::setActive(int pID) {
    playerID = pID;
    timeout = std::chrono::system_clock::now() + std::chrono::seconds(5);
    active = true;
}

void Bonus::setInactive() {
    active = false;
}
}
