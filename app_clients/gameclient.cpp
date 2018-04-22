#include "gameclient.h"

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
    qDebug()<<"Read data:"<<socket->readAll()<<"\n";
}
