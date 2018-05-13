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
#include "gamemode.h"
#include "board.h"


#include <QObject>
#include <QTimer>
#include <QDebug>

GameServer::GameServer(int argc, char *argv[], int numberOfPlayers, int numberOfPoints, int portNumber, QObject *parent) : QObject(parent), app(argc, argv), nPlayers(numberOfPlayers), currentNumberOfPlayers(0), numberOfActivePlayers(numberOfPlayers),
                                                                                                                           turnNumber(0), maxScore(numberOfPoints), dev(), gen(dev()), dist(0.1, 0.9)
{
    server = std::unique_ptr<QTcpServer>(new QTcpServer(this));
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::AnyIPv4, portNumber)) {
        qDebug() <<"Server could not start";
    } else {
        qDebug() <<"Server started";
    }
}

void GameServer::newConnection() {
    if(nPlayers == currentNumberOfPlayers) return;

    sockets.emplace_back(server->nextPendingConnection());
    buffers.emplace_back();
    players.emplace_back(currentNumberOfPlayers, dist(gen), dist(gen), dist(gen)*3.14);

    ++currentNumberOfPlayers;



    if(nPlayers == currentNumberOfPlayers) {
        for(int i = 0; i < nPlayers; ++i) {
            gamemode.addObserver(&players[i]);
        }
        Communication::GameStartMessage msg(nPlayers, maxScore);
        Communication::TranslatorToArray translator;
        translator.visit(msg);
        sendToAll(translator.getLastMessage());

        startGame();
    }
}

void GameServer::startGame() {
    qDebug()<<"Game started";
    for(int i = 0; i < nPlayers; ++i) {
        connect(sockets[i].get(), SIGNAL(readyRead()), this, SLOT(readData()));
    }
    connect(&timer, SIGNAL(timeout()), this, SLOT(performTurn()));
    timer.start(GamePlay::GamePlay::turnInterval);
}

int GameServer::exec() {
    return app.exec();
}

void GameServer::performTurn() {
    //qDebug()<<"Next turn";
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
    Communication::RoundEndMessage msg(nPlayers);
    Communication::TranslatorToArray translator;
    for(int i = 0; i < nPlayers; ++i) {
        msg.addScore(i, players[i].getScore());
        players[i].setCoordinatesAndAngle(dist(gen), dist(gen), 3.14*dist(gen));
        players[i].setActive();
    }
    translator.visit(msg);
    //gamemode.setMode(GamePlay::Mode::COLLISIONLESS, 0);
    board.eraseBoard();
    sendToAll(translator.getLastMessage());
    checkEndOfAllGames();

    numberOfActivePlayers = nPlayers;
    timer.start(GamePlay::GamePlay::turnInterval);
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

void GameServer::checkEndOfAllGames() {
    qDebug()<<"checking...";
    for(auto &p : players) {
        if(p.getScore() >= maxScore) {
            Communication::TranslatorToArray t;
            Communication::GameOverMessage m;
            m.accept(t);
            sendToAll(t.getLastMessage());
            qDebug()<<"end of all games";
            app.quit();
        }
    }
}

GameServer::~GameServer() {
    for(auto &socket : sockets)
        socket->close();
}


