#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <memory>
#include <vector>
#include <random>
#include <QObject>
#include <QCoreApplication>
#include <QtNetwork>
#include <QTimer>

#include "player.h"
#include "board.h"
#include "communication.h"
#include "message.h"
#include "gamemode.h"
#include "serverexception.h"

/**
 * @brief The GameServer class provides basic functionality connected with communicationg with client and organizing gameplay
 */
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
    void performDelay();

private:
    void startGame();
    void dispatchMessage(int playerIndex, std::unique_ptr<Communication::Message>);
    void sendToAll(const QByteArray &array) const;
    void endRound();
    bool checkEndOfAllGames();
    void resetDelay();
    void setDelayTimer();
    void checkBonusCollision(const GamePlay::Point& p);
    void manageBonuses();
    void reset();
    void sendInfoAboutSecondsOfDelay();
    void sendToAllWrapper(Communication::Message&&);

    QCoreApplication app;
    std::vector<QByteArray> buffers;
    std::unique_ptr<QTcpServer> server;
    std::vector<std::unique_ptr<QTcpSocket>> sockets;
    std::vector<GamePlay::Player>players;
    GamePlay::GameMode gamemode;
    QTimer timer;
    QTimer gameDelayTimer;
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
    int secondsOfDelayLeft;
    bool hasBeenReseted;
    int portNumber;
};

#endif // GAMESERVER_H
