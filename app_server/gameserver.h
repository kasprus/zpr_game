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
#include "communication.h"
#include "message.h"

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
    void readData();

private:
    void startGame();
    void dispatchMessage(int playerIndex, std::unique_ptr<Communication::Message>);
    void sendToAll(const QByteArray &array) const;
    std::vector<QByteArray> buffers;
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
