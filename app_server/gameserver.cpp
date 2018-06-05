#include <QtMath>
#include <QObject>
#include <QTimer>
#include <QDebug>

#include "gameserver.h"
#include "message.h"
#include "point.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "gameplay.h"
#include "communication.h"
#include "player.h"
#include "bonusmessage.h"
#include "gamestartmessage.h"
#include "gameovermessage.h"
#include "gamescoremessage.h"
#include "translatorfromarray.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "gamedelaymessage.h"
#include "gamemode.h"
#include "bonus.h"
#include "board.h"

GameServer::GameServer(int argc, char *argv[], int numberOfPlayers, int numberOfPoints, int portNumber, QObject *parent) : QObject(parent), app(argc, argv), nPlayers(numberOfPlayers), currentNumberOfPlayers(0), numberOfActivePlayers(numberOfPlayers),
                                                                                                                           turnNumber(0), maxScore(numberOfPoints), dev(), gen(dev()), dist(0.1, 0.9), hasBeenReseted(false), portNumber(portNumber)
{
    if(numberOfPlayers > GamePlay::GamePlay::maximumNumberOfPlayers || numberOfPlayers <= 0)throw WrongNumberOfPlayersException();
    server = std::unique_ptr<QTcpServer>(new QTcpServer(nullptr));
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::AnyIPv4, portNumber)) {
        qDebug() <<"Server could not start";
    } else {
        qDebug() <<"Server started";
    }
}

void GameServer::newConnection() {
    if(nPlayers == currentNumberOfPlayers) {
        return;
    }
    sockets.emplace_back(server->nextPendingConnection());
    buffers.emplace_back();
    players.emplace_back(currentNumberOfPlayers, dist(gen), dist(gen), dist(gen)*M_PI);
    ++currentNumberOfPlayers;
    if(nPlayers == currentNumberOfPlayers) {
        server->close();
        for(int i = 0; i < nPlayers; ++i) {
            gamemode.addObserver(&players[i]);
            Communication::GameStartMessage msg(nPlayers, maxScore, i);
            Communication::TranslatorToArray translator;
            translator.visit(msg);
            sockets[i]->write(translator.getLastMessage());
            sockets[i]->flush();
        }
        startGame();
    }
}

void GameServer::startGame() {
    qDebug()<<"Game started";
    for(int i = 0; i < nPlayers; ++i) {
        connect(sockets[i].get(), SIGNAL(readyRead()), this, SLOT(readData()));
    }
    if(!hasBeenReseted) {
        connect(&timer, SIGNAL(timeout()), this, SLOT(performTurn()));
        connect(&gameDelayTimer, SIGNAL(timeout()), this, SLOT(performDelay()));
    }
    resetDelay();
    setDelayTimer();
}

int GameServer::exec() {
    return app.exec();
}

void GameServer::performTurn() {
    for(int i = 0; i < nPlayers; ++i) {
        Communication::PointMessage msg;
        if(players[i].isActive()) {
            GamePlay::Point p = players[i].move(turnNumber);
            if(board.checkCollision(p)) {
                players[i].setInactive();
                Communication::GameScoreMessage scoreMessage(nPlayers);
                for(int j = 0; j < nPlayers; ++j) {
                    if(players[j].isActive())
                        players[j].addScore(1);
                    scoreMessage.addScore(j, players[j].getScore());

                }




                sendToAllWrapper(std::move(scoreMessage));

                --numberOfActivePlayers;

            }
            checkBonusCollision(p);
            if(p.isVisible())
                board.registerPoint(p);
            msg.addPoint(p);
            sendToAllWrapper(std::move(msg));
        }
    }
    if(turnNumber % GamePlay::GamePlay::intervalBetweenBonusManagement == 0) {
        manageBonuses();
    }
    if(numberOfActivePlayers == 0) {
        timer.stop();
        endRound();
    }
    ++turnNumber;
}

void GameServer::checkBonusCollision(const GamePlay::Point& p) {
    GamePlay::Bonus res = board.checkBonusCollision(p);
    if(res.getMode() != -1) {
        qDebug() << "remove in check";
        sendToAllWrapper(Communication::BonusMessage(res, false));
        board.removeBonus(res.getMode());
        res.setActive(p.getPlayerId());
        gamemode.updateBonus(res);
    }
}

void GameServer::manageBonuses() {
    GamePlay::Bonus oldBonus = gamemode.checkTimeout();

    while(oldBonus.getMode() != -1) {
        if(!oldBonus.isActive()) {
            qDebug() << "REMOVE IN MANAGE";
            board.removeBonus(oldBonus.getMode());
            sendToAllWrapper(Communication::BonusMessage(oldBonus, false));
        }
        oldBonus.setInactive();
        gamemode.updateBonus(oldBonus);

        oldBonus = gamemode.checkTimeout();
    }


    GamePlay::Bonus newBonus = gamemode.tryBonus();
    if(newBonus.getMode() != GamePlay::Modes::EMPTY_BONUS) {
        board.registerBonus(newBonus);
        sendToAllWrapper(Communication::BonusMessage(newBonus, true));
    }
}

void GameServer::endRound() {
    timer.stop();
    for(int i = 0; i < nPlayers; ++i) {
        players[i].setCoordinatesAndAngle(dist(gen), dist(gen), M_PI*dist(gen));
        players[i].setActive();
        players[i].reset();
    }
    board.eraseBoard();
    gamemode.removeAllBonuses();
    sendToAllWrapper(Communication::RoundEndMessage());
    if(!checkEndOfAllGames()) {
        numberOfActivePlayers = nPlayers;
        resetDelay();
        setDelayTimer();
    }
}
void GameServer::readData() {
    int socketIndex = 0;
    for(; sockets[socketIndex].get() != sender(); ++socketIndex) {
    }
    QByteArray tmp = sockets[socketIndex]->readAll();
    for(auto byte : tmp) {
        buffers[socketIndex].append(byte);
        if(buffers[socketIndex].size() == Communication::Communication::messageSize) {
            Communication::TranslatorFromArray translator;
            auto message = translator.getMessage(buffers[socketIndex]);
            dispatchMessage(socketIndex, std::move(message));
            buffers[socketIndex].clear();
        }
    }
}

void GameServer::dispatchMessage(int playerIndex, std::unique_ptr<Communication::Message> message) {
    if(message->getHeader() == Communication::Communication::keyPressedMessageHeader) {
        int key = dynamic_cast<Communication::KeyPressedMessage*>(message.get())->getKeyId();
        if(key == Communication::Communication::leftKeyId) {
            players.at(playerIndex).setRotatingLeft();
        }
        if(key == Communication::Communication::rightKeyId) {
            players.at(playerIndex).setRotatingRight();
        }
    }
    else if(message->getHeader() == Communication::Communication::keyReleasedMessageHeader) {
        int key = dynamic_cast<Communication::KeyReleasedMessage*>(message.get())->getKeyId();
        if(key == Communication::Communication::leftKeyId) {
            players.at(playerIndex).cancelRotatingLeft();
        }
        if(key == Communication::Communication::rightKeyId) {
            players.at(playerIndex).cancelRotatingRight();
        }
    }
    else {
        throw UnsupportedServerMessageException();
    }
}

void GameServer::sendToAll(const QByteArray& array) const {
    for(auto &socket : sockets) {
        socket->write(array);
        socket->flush();
    }
}

bool GameServer::checkEndOfAllGames() {
    auto findWinner = [this]() -> int {
        int w = 0;
        for(int i = 0; i < nPlayers; ++i) {
            if(players[i].getScore() > players[w].getScore()) {
                w = i;
            }
        }
        return w;
    };
    for(auto &p : players) {
        if(p.getScore() >= maxScore) {
            sendToAllWrapper(Communication::GameOverMessage(findWinner()));
            reset();
            return true;
        }
    }
    return false;
}

void GameServer::resetDelay() {
    secondsOfDelayLeft = GamePlay::GamePlay::secondsOfGameDelay;
}

void GameServer::setDelayTimer() {
    gameDelayTimer.start(1000);
    sendInfoAboutSecondsOfDelay();
}

void GameServer::performDelay() {
    if(--secondsOfDelayLeft <= 0) {
        gameDelayTimer.stop();
        timer.start(GamePlay::GamePlay::turnInterval);
    }
    sendInfoAboutSecondsOfDelay();
}

void GameServer::sendInfoAboutSecondsOfDelay() {
    sendToAllWrapper(Communication::GameDelayMessage(secondsOfDelayLeft));
}

void GameServer::reset() {
    for(auto &s : sockets) {
        s->close();
    }
    sockets.clear();
    server = std::unique_ptr<QTcpServer>(new QTcpServer(nullptr));
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::AnyIPv4, portNumber)) {
        qDebug() <<"Server could not start";
    } else {
        qDebug() <<"Server started";
    }
    players.clear();
    currentNumberOfPlayers = 0;
    numberOfActivePlayers = nPlayers;
    turnNumber = 0;
    hasBeenReseted = true;
}

void GameServer::sendToAllWrapper(Communication::Message&& m) {
    Communication::TranslatorToArray t;
    m.accept(t);
    sendToAll(t.getLastMessage());
}

GameServer::~GameServer() {
    for(auto &socket : sockets)
        socket->close();
}

