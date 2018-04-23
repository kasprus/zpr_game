#include "gameclient.h"
#include "communication.h"
#include "message.h"
#include "pointmessage.h"
#include "translatorfromarray.h"
#include "translatortoarray.h"

GameClient::GameClient(QObject *parent) : QObject(parent)
{
    socket = std::unique_ptr<QTcpSocket>(new QTcpSocket(this));
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(readData()));
    socket->connectToHost("127.0.0.1", 4321);
    if(socket->waitForConnected()) {
        qDebug() <<"Connection started";
    } else {
        qDebug() <<"Connection failed";
    }
}

GameClient::~GameClient() {
    if(socket && socket->isOpen())
        socket->close();
}

void GameClient::readData() {
    QByteArray tmp = socket->readAll();
    Communication::TranslatorFromArray translator;
    for(auto byte : tmp) {
        buffer.append(byte);
        if(buffer.size() == Communication::Communication::messageSize) {
            responseForMessage(translator.getMessage(buffer));
        }
    }
}

void GameClient::responseForMessage(std::unique_ptr<Communication::Message> msg) {
    if(msg->getHeader() == Communication::Communication::pointMessageHeader) {
        qDebug()<<"New point!\n";
    }
}
