#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <memory>
#include "point.h"
#include "message.h"


class GameClient : public QObject
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
    virtual ~GameClient();
signals:
    void newPoint(GamePlay::Point);
public slots:
    void readData();
    void writeData(QByteArray data);
    void establishConnection(QString ip);
private:
    void responseForMessage(std::unique_ptr<Communication::Message> msg);
    std::unique_ptr<QTcpSocket> socket;
    QByteArray buffer;
};

#endif // GAMECLIENT_H
