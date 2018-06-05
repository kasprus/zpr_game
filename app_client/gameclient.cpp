#include <QDebug>
#include <QString>

#include "clientexception.h"
#include "gameclient.h"
#include "bonusmessage.h"
#include "communication.h"
#include "message.h"
#include "pointmessage.h"
#include "gamestartmessage.h"
#include "roundendmessage.h"
#include "gamedelaymessage.h"
#include "gameovermessage.h"
#include "translatorfromarray.h"
#include "translatortoarray.h"

GameClient::GameClient(QObject *parent) : QObject(parent)
{
}

GameClient::~GameClient() {
    if(socket && socket->isOpen())
        socket->close();
}

void GameClient::establishConnection(QString ip, qint32 port) {
    lastIP = ip;
    lastPort = port;
    socket = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost(ip, port);
    if(socket->waitForConnected()) {
        qDebug() <<"Connection started";
        emit newConnectionMessage(true);
    } else {
        emit newConnectionMessage(false);
        qDebug() <<"Connection failed";
    }
}

void GameClient::reconnect() {
    establishConnection(lastIP, lastPort);
}

void GameClient::readData() {
//    qDebug()<<"new data";
    if(!socket)return;
    QByteArray tmp = socket->readAll();
    Communication::TranslatorFromArray translator;
    for(auto byte : tmp) {
        buffer.append(byte);
        if(buffer.size() == Communication::Communication::messageSize) {
            responseForMessage(translator.getMessage(buffer));
            buffer.clear();
        }
    }
}

void GameClient::responseForMessage(std::unique_ptr<Communication::Message> msg) {
    if(msg->getHeader() == Communication::Communication::pointMessageHeader) {
        //qDebug() << "Point Message";
        auto points = dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints();
//        qDebug() <<"Number of points: "<<points.size();
        for(auto &p : points) {
//            qDebug() <<"Emining new point";
            emit newPoint(p);
        }
    }
    else if (msg->getHeader() == Communication::Communication::roundEndMessageHeader) {
        qDebug() << "Round Ended";
        std::vector<int> scr = dynamic_cast<Communication::RoundEndMessage*>(msg.get())->getScore();
        emit endRound(scr);
    }
    else if (msg->getHeader() == Communication::Communication::gameStartMessageHeader) {
        qDebug() << "Game Starts...";
        auto m = dynamic_cast<Communication::GameStartMessage*>(msg.get());
        qint32 nPlayers = m->getNumberOfPlayers();
        qint32 maxScore = m->getMaxScore();
        qint32 playerNumber = m->getPlayerNumber();
        emit setWindow(nPlayers, maxScore, playerNumber);
    }
    else if (msg->getHeader() == Communication::Communication::gameOverMessageHeader) {
        qDebug() << "Game over";
        emit gameOver(dynamic_cast<Communication::GameOverMessage*>(msg.get())->getWinner());
    }
    else if(msg->getHeader() == Communication::Communication::gameDelayMessageHeader) {
        qDebug() << "Dealy" << dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getDelay();
        emit gameDelay(dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getDelay());
    }
    else if (msg->getHeader() == Communication::Communication::bonusMessageHeader) {
        qDebug() << "Bonus";
        auto m = dynamic_cast<Communication::BonusMessage*>(msg.get());
        qint32 mode = m->getMode();
        qreal x = m->getX();
        qreal y = m->getY();
        qint8 show = m->getShowBonus();
        emit newBonus(mode, x, y, show);
    } else {
        throw UnsupportedClientMessageException();
    }
}

void GameClient::writeData(QByteArray data) {
    if(!socket)return;
    qDebug()<<"sending some data";
    socket->write(data);
    socket->flush();
}
