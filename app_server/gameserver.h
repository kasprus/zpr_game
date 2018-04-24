#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <memory>
#include <vector>
#include <QTimer>
#include "player.h"
#include "board.h"

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(int numberOfPlayers, QObject *parent = 0);
    virtual ~GameServer();
signals:

public slots:
    void newConnection();
    void performTurn();

private:
    void startGame();
    std::unique_ptr<QTcpServer> server;
    std::vector<std::unique_ptr<QTcpSocket>> sockets;
    std::vector<GamePlay::Player>players;
    QTimer timer;
    GamePlay::Board board;
    int nPlayers;
    int currentNumberOfPlayers;
    long turnNumber;
};

#endif // GAMESERVER_H
