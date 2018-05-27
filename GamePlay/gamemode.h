#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <chrono>
#include <memory>
#include <random>
#include <vector>
#include "bonus.h"
#include "modes.h"
#include "player.h"

namespace GamePlay {

class GameMode;
class Player;
class Bonus;

class GameMode {
public:

    GameMode();
    void addObserver(Player* obs);

    void removeAllBonuses();
    Bonus tryBonus();
    Bonus checkTimeout();
    void updateBonus(const Bonus& bonus);
    double getBonusX(int mode) const;
    double getBonusY(int mode) const;
    std::chrono::system_clock::time_point getTimeout(int mode) const;

private:
    std::vector<Player*> observerPlayers;
    std::vector<std::unique_ptr<Bonus> > bonuses;
    void notifyPlayers(const Bonus& bonus);
    bool checkIfEligible(int mode);
    std::random_device dev;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> distBonus;
    std::uniform_int_distribution<int> distMode;
    std::uniform_real_distribution<double> distPos;
    constexpr const static int bonusChance = 50;
};

}

#endif // GAMEMODE_H
