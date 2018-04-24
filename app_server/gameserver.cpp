#include "gameserver.h"
#include "message.h"
#include "point.h"
#include "pointmessage.h"
#include "translatortoarray.h"
#include "gameplay.h"
#include "player.h"
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

GameServer::~GameServer() {
    for(auto &socket : sockets)
        socket->close();
}


