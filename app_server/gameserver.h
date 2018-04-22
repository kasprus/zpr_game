#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <memory>

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(QObject *parent = 0);
signals:

public slots:
    void newConnection();

private:
    std::unique_ptr<QTcpServer> server;
};

#endif // GAMESERVER_H
