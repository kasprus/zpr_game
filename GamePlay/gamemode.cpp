#include "gamemode.h"
#include "bonus.h"
#include "modes.h"

namespace GamePlay {


GameMode::GameMode() : bonuses(Modes::MODESCOUNT), dev(), gen(dev()), distBonus(0, 99), distMode(0, Modes::MODESCOUNT-1), distPos(0.1, 0.9 )
{
}

void GameMode::addObserver(Player* obs) {
    observerPlayers.push_back(obs);
}

void GameMode::notifyPlayers(const Bonus& bonus) {
    for(auto player : observerPlayers) {
        player->updateMode(bonus);
    }

}

Bonus GameMode::tryBonus() {
    int num = distBonus(gen);
    if(num < bonusChance) {
        int mode = distMode(gen);

        if(!checkIfEligible(mode)) return Bonus(-1);

        auto timeout = std::chrono::system_clock::now(); timeout += std::chrono::seconds(12);
        bonuses[mode] = std::move(std::unique_ptr<Bonus>(new Bonus(mode, -1, timeout, distPos(gen), distPos(gen))));
        return Bonus(*(bonuses[mode].get()));
    }
    return Bonus(-1);
}

bool GameMode::checkIfEligible(int mode) {
    switch(mode) {
    case Modes::FAST:
        /* fall through */
    case Modes::FAST_O:
        /* fall through */
    case Modes::SLOW:
        /* fall through */
    case Modes::SLOW_O:
        if(bonuses[Modes::FAST] || bonuses[Modes::FAST_O] || bonuses[Modes::SLOW] || bonuses[Modes::SLOW_O])
          return false;
        break;
    case Modes::THICK:
        /* fall through */
    case Modes::THICK_O:
        /* fall through */
    case Modes::THIN:
        /* fall through */
    case Modes::THIN_O:
        if(bonuses[Modes::THICK] || bonuses[Modes::THICK_O] || bonuses[Modes::THIN] || bonuses[Modes::THIN_O])
          return false;
        break;
    case Modes::SQUARE:
        /* fall through */
    case Modes::SQUARE_O:
        if(bonuses[Modes::SQUARE] || bonuses[Modes::SQUARE_O])
            return false;
        break;
    case Modes::REVERSE:
        /* fall through */
    case Modes::REVERSE_O:
        if(bonuses[Modes::REVERSE] || bonuses[Modes::REVERSE_O])
            return false;
        break;
    case Modes::COLLISIONLESS:
        if(bonuses[Modes::COLLISIONLESS])
            return false;
    }
    return true;
}

double GameMode::getBonusX(int mode) const {
    if(bonuses[mode])
        return bonuses[mode]->getX();
    else return -1;
}

double GameMode::getBonusY(int mode) const {
    if(bonuses[mode])
        return bonuses[mode]->getY();
    else return -1;
}

Bonus GameMode::getBonus(int mode) const {
    if(bonuses[mode])
        return Bonus(*(bonuses[mode].get()));
    else
        return Bonus(GamePlay::Modes::EMPTY_BONUS);
}



Bonus GameMode::checkTimeout() {

    for(auto& it : bonuses) {
        if(it.get() &&  it->getTimeout() <= std::chrono::system_clock::now()) {
            Bonus bns(*(it.get()));
            it.reset();
            return bns;
        }
    }

    return Bonus(-1);
}

void GameMode::updateBonus(const Bonus& bonus) {
   if(bonus.isActive()) {
        bonuses[bonus.getMode()]->setActive(bonus.getPlayerID());
   }
   notifyPlayers(bonus);
}

void GameMode::removeAllBonuses() {
    for(auto& it : bonuses) {
        if(it.get()) {
            it.reset();
        }
    }
    notifyPlayers(Bonus(Modes::NORMAL));
}

}

