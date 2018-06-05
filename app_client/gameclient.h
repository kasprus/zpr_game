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
#include "controller.h"

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
    void setController(Controller* controller);
signals:
    /**
     * @brief Called when connection is established or failed.
     * @param status True if connection is established.
     */
    void newConnectionMessage(bool);


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

    /**
     * @brief Tries to reconnect to server
     */
    void reconnect();
private:
    void responseForMessage(std::unique_ptr<Communication::Message> msg);
    std::unique_ptr<QTcpSocket> socket;
    QByteArray buffer;
    QString lastIP;
    qint32 lastPort;
    Controller* controller;
};

#endif // GAMECLIENT_H
