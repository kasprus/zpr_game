#include "gamemode.h"
#include "bonus.h"
#include "modes.h"
#include "QDebug"
namespace GamePlay {


GameMode::GameMode() : bonuses(Modes::MODESCOUNT), dev(), gen(dev()), distBonus(0, 9), distMode(0, Modes::MODESCOUNT-1), distPos(0.1, 0.9 )
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
    if(num < 7) {
        int mode = distMode(gen);
        if( mode > 11 && bonuses[mode] ) return Bonus(-1);
         if(bonuses[mode/2*2]) return Bonus(-1);

        auto timeout = std::chrono::system_clock::now(); timeout += std::chrono::seconds(12);
        bonuses[mode] = std::move(std::unique_ptr<Bonus>(new Bonus(mode, -1, timeout, distPos(gen), distPos(gen)))); // todo: send message. here?
        return Bonus(*(bonuses[mode].get()));
    }
    return Bonus(-1);
}

double GameMode::getBonusX(int mode) const {
    return bonuses[mode]->getX();
}

double GameMode::getBonusY(int mode) const {
    return bonuses[mode]->getY();
}

std::chrono::system_clock::time_point GameMode::getTimeout(int mode) const {
    return bonuses[mode]->getTimeout();
}

Bonus GameMode::checkTimeout() {
    //qDebug() << "begin check timeout";
    for(auto& it : bonuses) {
        if(it.get() &&  it->getTimeout() <= std::chrono::system_clock::now()) {
            Bonus bns(*(it.get()));
            it.reset();
            return bns;
        }
    }
     //qDebug() << "end check timeout";
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
        if(it.get())
            it.reset();
    }
    notifyPlayers(Bonus(Modes::NORMAL));
}

}

