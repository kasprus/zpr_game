#include "gameserver.h"
#include "message.h"
#include "point.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "gameplay.h"
#include "communication.h"
#include "player.h"
#include "translatorfromarray.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include <QObject>
#include <QTimer>
#include <QDebug>

GameServer::GameServer(int numberOfPlayers, QObject *parent) : QObject(parent), nPlayers(numberOfPlayers), currentNumberOfPlayers(0), turnNumber(0)
{
    server = std::unique_ptr<QTcpServer>(new QTcpServer(this));
    connect(server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::AnyIPv4, 4321)) {
        qDebug() <<"Server could not start";
    } else {
        qDebug() <<"Server started";
    }
}

void GameServer::newConnection() {
    if(nPlayers == currentNumberOfPlayers)return;
    ++currentNumberOfPlayers;
    sockets.emplace_back(server->nextPendingConnection());
    buffers.emplace_back();
    players.emplace_back(currentNumberOfPlayers, GamePlay::Board::dimensionX / (currentNumberOfPlayers + 2), GamePlay::Board::dimensionY / (currentNumberOfPlayers + 2), 0);
    if(nPlayers == currentNumberOfPlayers)startGame();
//    Communication::PointMessage msg;
//    Communication::TranslatorToArray translator;
//    GamePlay::Point p1(0.8, 0.5, 0.1, 1, 1);
//    GamePlay::Point p2(0.9, 0.2, 0.1, 1, 1);
//    msg.addPoint(p1);
//    msg.addPoint(p2);
//    translator.visit(msg);
//    socket->write(translator.getLastMessage());
//    socket->flush();
//    socket->waitForBytesWritten(2000);
//    socket->close();
}

void GameServer::startGame() {
    qDebug()<<"Game started";
    for(int i = 0; i < nPlayers; ++i) {
        connect(sockets[i].get(), SIGNAL(readyRead()), this, SLOT(readData()));
    }
    connect(&timer, SIGNAL(timeout()), this, SLOT(performTurn()));
    //
    timer.start(GamePlay::GamePlay::turnInterval);
}

void GameServer::performTurn() {
    qDebug()<<"Next turn";
    for(int i = 0; i < nPlayers; ++i) {
        Communication::PointMessage msg;
        Communication::TranslatorToArray translator;
        players[i].move();
        GamePlay::Point p = players[i].getPoint(turnNumber);
        msg.addPoint(p);
        translator.visit(msg);
        sockets[i]->write(translator.getLastMessage());
        sockets[i]->flush();
    }
    ++turnNumber;
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

GameServer::~GameServer() {
    for(auto &socket : sockets)
        socket->close();
}


