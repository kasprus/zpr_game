#include "gamemode.h"

namespace GamePlay {

GameMode::GameMode() : currentMode(Mode::NORMAL)
{
}

void GameMode::addObserver(Player* obs) {
    observerPlayers.push_back(obs);
}

void GameMode::notifyPlayers() {
    for(auto player : observerPlayers) {
        player->updateMode(Mode(currentMode), playerID);
    }
}

void GameMode::setTimeout(int timeout_) {
    timeout = timeout_;
}

void GameMode::setMode(Mode mode, int id) {
    currentMode = mode;
    playerID = id;
    notifyPlayers();
}

}

