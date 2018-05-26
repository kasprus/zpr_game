#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <memory>
#include <vector>
#include "point.h"
#include "message.h"

/**
 * @brief This class provides the implementation of the network client.
 */
class GameClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs object.
     * @param parent Optional argument. Parent object.
     */
    explicit GameClient(QObject *parent = 0);
    virtual ~GameClient();
signals:
    /**
     * @brief Called when connection is established or failed.
     * @param status True if connection is established.
     */
    void newConnectionMessage(bool);
    /**
     * @brief Called when new point should be processed by controller.
     * @param point New point.
     */
    void newPoint(GamePlay::Point point);
    /**
     * @brief Called when round should be finished.
     * @param scores Scores achieved by players
     */
    void endRound(const std::vector<int>& scores);

    void setWindow(qint32, qint32, qint32);

    /**
     * @brief Called when delay between rounds should be set.
     * @param delay Required delay
     */
    void gameDelay(qint32 delay);

    /**
     * @brief Called when game should be finished.
     */
    void gameOver(int winner);
public slots:

    /**
     * @brief Reads data received from the server.
     */
    void readData();

    /**
     * @brief Sends data to the server.
     * @param data Array of bytes to send.
     */
    void writeData(QByteArray data);

    /**
     * @brief Creates tcp connection with the server.
     * @param ip Ip address
     * @param port Port number
     */
    void establishConnection(QString ip, qint32 port);
private:
    void responseForMessage(std::unique_ptr<Communication::Message> msg);
    std::unique_ptr<QTcpSocket> socket;
    QByteArray buffer;
};

#endif // GAMECLIENT_H
