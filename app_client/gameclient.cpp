#include <iostream>
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
        std::cout << "Connection started\n";
        emit newConnectionMessage(true);
    } else {
        emit newConnectionMessage(false);
        std::cout << "Connection failed\n";
    }
}

void GameClient::reconnect() {
    establishConnection(lastIP, lastPort);
}

void GameClient::readData() {
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
    msg->accept(*controller);
}

void GameClient::setController(Controller *controller_) {
    controller = controller_;    
}

void GameClient::writeData(QByteArray data) {
    if(!socket)return;
    socket->write(data);
    socket->flush();
}
