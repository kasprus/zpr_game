#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <memory>
#include <vector>
#include "point.h"
#include "message.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "addressdialog.h"
#include "mainwindow.h"

class GameClient;

/**
 * @brief This class provides basic controller functionality. It is responsible for reacting for user input, preparing views and and providing data for web client.
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs controller.
     * @param client Network client for sending end geting messages.
     * @param parent The parameter specifies parent of the object for memory management and is optional.
     */
    explicit Controller(GameClient& client, QObject *parent = 0);
    /**
     * @brief It sets size of the playing board.
     * @param size Number of pixels.
     */
    void setBoardPixelSize(int size);
    /**
     * @brief It shows the user a dialog box to enter server parameters.
     */
    void showIpDialog();
signals:
    /**
     * @brief Called when new circle should be drawn.
     * @param x X relative coordinate of the object.
     * @param y Y relative coordinate of the object.
     * @param radius Radius of the object.
     * @param pId Number of player to whom the circle belongs.
     * @param isVisible True if circle is visible
     */
    void newCircle(qreal x, qreal y, qreal radius, qint32 pId, bool isVisible);

    /**
     * @brief Called when game parameters and scene should be drawn.
     * @param nPlayers Number of players of the game.
     * @param maxScore Maximum score of the game.
     */
    void setWindows(qint32 nPlayers, qint32 maxScore, qint32 playerNumber);

    /**
     * @brief Called when round is finished and board should be cleared.
     * @param scr Scores of players achieved in the round.
     */
    void endRoundAndClear(const std::vector<int>& scr);

    /**
     * @brief Called when new message should be sent to server.
     */
    void newDataToWrite(QByteArray);

    /**
     * @brief Called when server parameters are provided.
     * @param ip IP address of the server.
     * @param port Port number of the server.
     */
    void newConnectionInfo(QString ip, qint32 port);

    /**
     * @brief Called when new message should be presented on the scene.
     * @param message Message.
     */
    void newSceneMessage(QString message);

    /**
     * @brief Called when scene messages should be cleared.
     */
    void clearMessages();

public slots:
    //Trzeba zmienić nazwę, bo jest myląca
    void setWindow(qint32, qint32, qint32);

    /**
     * @brief Deals with new point.
     * @param point Game point.
     */
    void newPoint(GamePlay::Point point);

    /**
     * @brief It finishes the game round.
     * @param scr Scores achieved by players in the round.
     */
    void endRound(const std::vector<int>&scr);

    /**
     * @brief It reacts to message with information about pressed key.
     * @param msg Message about pressed key.
     */
    void newKeyPressedMessageToSend(Communication::KeyPressedMessage msg);

    /**
     * @brief It reacts to message with information about released key.
     * @param msg Message about released key.
     */
    void newKeyReleasedMessageToSend(Communication::KeyReleasedMessage msg);

    /**
     * @brief It emits signals with connection with the server parameters.
     */
    void generateConnectionInfo();

    /**
     * @brief It finishes whole game.
     * @param Number of the winner
     */
    void gameOver(int winner);

    /**
     * @brief It is responsible for providing required delay between rounds.
     * @param delay Length of the delay in seconds.
     */
    void gameDelay(qint32 delay);

    /**
     * @brief Deals with information about connection.
     * @param status Status of the connection.
     */
    void newConnection(bool status);

    /**
     * @brief Sets colors
     */
    void setColors(std::vector<std::string>colors);

private:
    qreal boardPixelSize;
    AddressDialog ipDialog;
    std::vector<std::string>colorNames;
};

#endif // CONTROLLER_H
