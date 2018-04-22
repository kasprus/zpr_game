#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>
#include <memory>


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
    std::unique_ptr<QTcpSocket> socket;

};

#endif // GAMECLIENT_H
