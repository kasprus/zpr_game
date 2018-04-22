#include "gameserver.h"

GameServer::GameServer(QObject *parent) : QObject(parent)
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
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write("dupa");
    socket->flush();
    socket->waitForBytesWritten(2000);
    socket->close();
}


