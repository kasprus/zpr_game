#include "gameclient.h"
#include "communication.h"
#include "message.h"
#include "pointmessage.h"
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

void GameClient::establishConnection(QString ip) {
    socket = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost(ip, 4321);
    if(socket->waitForConnected()) {
        qDebug() <<"Connection started";
    } else {
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
        auto points = dynamic_cast<Communication::PointMessage*>(msg.get())->getPoints();
//        qDebug() <<"Number of points: "<<points.size();
        for(auto &p : points) {
//            qDebug() <<"Emining new point";
            emit newPoint(p);
        }
    }
}

void GameClient::writeData(QByteArray data) {
    if(!socket)return;
    qDebug()<<"sending some data";
    socket->write(data);
    socket->flush();
}
