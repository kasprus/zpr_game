#include "gameclient.h"
#include "communication.h"
#include "message.h"
#include "pointmessage.h"
#include "gamestartmessage.h"
#include "gameendmessage.h"
#include "roundendmessage.h"
#include "gamedelaymessage.h"
#include "translatorfromarray.h"
#include "translatortoarray.h"
#include <QDebug>
#include <QString>

GameClient::GameClient(QObject *parent) : QObject(parent)
{
}

GameClient::~GameClient() {
    if(socket && socket->isOpen())
        socket->close();
}

void GameClient::establishConnection(QString ip, qint32 port) {
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
        qDebug() << "Point Message";
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

        emit setWindow(nPlayers, maxScore);
    }
    else if (msg->getHeader() == Communication::Communication::gameOverMessageHeader) {
        qDebug() << "Game over";
        emit gameOver();
    }
    else if(msg->getHeader() == Communication::Communication::gameDelayMessageHeader) {
        qDebug() << "Dealy" << dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getDelay();
        emit gameDelay(dynamic_cast<Communication::GameDelayMessage*>(msg.get())->getDelay());
    }
}

void GameClient::writeData(QByteArray data) {
    if(!socket)return;
    qDebug()<<"sending some data";
    socket->write(data);
    socket->flush();
}
