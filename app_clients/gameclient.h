#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <memory>
#include "message.h"


class GameClient : public QObject
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
    virtual ~GameClient();
signals:

public slots:
    void readData();

private:
    void responseForMessage(std::unique_ptr<Communication::Message> msg);
    std::unique_ptr<QTcpSocket> socket;
    QByteArray buffer;
};

#endif // GAMECLIENT_H
