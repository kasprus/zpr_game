#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QObject>
#include <QCoreApplication>
#include <QtNetwork>
#include <QDebug>
#include <memory>
#include <vector>
#include <random>
#include <QTimer>
#include "player.h"
#include "board.h"
#include "communication.h"
#include "message.h"
#include "gamemode.h"

class GameServer : public QObject
{
    Q_OBJECT
public:
    explicit GameServer(int argc, char *argv[], int numberOfPlayers, int numberOfPoints, int portNumber, QObject *parent = 0);
    virtual ~GameServer();
    int exec();
signals:

public slots:
    void newConnection();
    void performTurn();
    void readData();

private:
    void startGame();
    void dispatchMessage(int playerIndex, std::unique_ptr<Communication::Message>);
    void sendToAll(const QByteArray &array) const;
    void endRound();
    void checkEndOfAllGames();

    QCoreApplication app;
    std::vector<QByteArray> buffers;
    std::unique_ptr<QTcpServer> server;
    std::vector<std::unique_ptr<QTcpSocket>> sockets;
    std::vector<GamePlay::Player>players;
    GamePlay::GameMode gamemode;
    QTimer timer;
    GamePlay::Board board;

    int nPlayers;
    int nPoints;
    int currentNumberOfPlayers;
    int numberOfActivePlayers;
    long turnNumber;
    int maxScore;
    std::random_device dev;
    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist;
};

#endif // GAMESERVER_H
