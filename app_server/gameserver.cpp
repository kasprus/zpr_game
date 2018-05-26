#include "gameserver.h"
#include "message.h"
#include "point.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "gameplay.h"
#include "communication.h"
#include "player.h"
#include "gamestartmessage.h"
#include "gameovermessage.h"
#include "translatorfromarray.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "gamedelaymessage.h"
#include "gamemode.h"
#include "board.h"

#include <QtMath>
#include <QObject>
#include <QTimer>
#include <QDebug>

GameServer::GameServer(int argc, char *argv[], int numberOfPlayers, int numberOfPoints, int portNumber, QObject *parent) : QObject(parent), app(argc, argv), nPlayers(numberOfPlayers), currentNumberOfPlayers(0), numberOfActivePlayers(numberOfPlayers),
                                                                                                                           turnNumber(0), maxScore(numberOfPoints), dev(), gen(dev()), dist(0.1, 0.9), hasBeenReseted(false), portNumber(portNumber)
{
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
        Communication::TranslatorToArray translator;
        if(players[i].isActive()) {
            GamePlay::Point p = players[i].move(turnNumber);
            if(board.checkCollision(p)) {
                players[i].addScore(nPlayers - numberOfActivePlayers);
                --numberOfActivePlayers;
                players[i].setInactive();
            }
            if(p.isVisible())
                board.registerPoint(p);
            msg.addPoint(p);
            translator.visit(msg);
            sendToAll(translator.getLastMessage());
        }
    }
    if(numberOfActivePlayers == 0) {
        timer.stop();
        endRound();
    }


    ++turnNumber;
}
void GameServer::endRound() {
    timer.stop();
    Communication::RoundEndMessage msg(nPlayers);
    Communication::TranslatorToArray translator;
    for(int i = 0; i < nPlayers; ++i) {
        msg.addScore(i, players[i].getScore());
        players[i].setCoordinatesAndAngle(dist(gen), dist(gen), M_PI*dist(gen));
        players[i].setActive();
    }
    translator.visit(msg);
    //gamemode.setMode(GamePlay::Mode::COLLISIONLESS, 0);
    board.eraseBoard();
    sendToAll(translator.getLastMessage());

    if(!checkEndOfAllGames()) {
        numberOfActivePlayers = nPlayers;
    //    timer.start(GamePlay::GamePlay::turnInterval);
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
            players[playerIndex].setRotatingLeft();
        }
        if(key == Communication::Communication::rightKeyId) {
            players[playerIndex].setRotatingRight();
        }
    }
    else if(message->getHeader() == Communication::Communication::keyReleasedMessageHeader) {
        int key = dynamic_cast<Communication::KeyReleasedMessage*>(message.get())->getKeyId();
        if(key == Communication::Communication::leftKeyId) {
            players[playerIndex].cancelRotatingLeft();
        }
        if(key == Communication::Communication::rightKeyId) {
            players[playerIndex].cancelRotatingRight();
        }
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
    qDebug()<<"checking...";
    for(auto &p : players) {
        if(p.getScore() >= maxScore) {
            Communication::TranslatorToArray t;
            Communication::GameOverMessage m(findWinner());
            m.accept(t);
            sendToAll(t.getLastMessage());
            qDebug()<<"end of all games";
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
    Communication::TranslatorToArray t;
    Communication::GameDelayMessage m(secondsOfDelayLeft);
    m.accept(t);
    sendToAll(t.getLastMessage());
}

void GameServer::performDelay() {
    if(--secondsOfDelayLeft <= 0) {
        gameDelayTimer.stop();
        timer.start(GamePlay::GamePlay::turnInterval);
    }
    Communication::TranslatorToArray t;
    Communication::GameDelayMessage m(secondsOfDelayLeft);
    m.accept(t);
    sendToAll(t.getLastMessage());

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

GameServer::~GameServer() {
    for(auto &socket : sockets)
        socket->close();
}

