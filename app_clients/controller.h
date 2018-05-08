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

class GameClient;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(GameClient& client, QObject *parent = 0);
    void setBoardPixelSize(int size);
    void showIpDialog();
signals:
    void newCircle(qreal x, qreal y, qreal radius, qint32 pId);
    void setWindows(qint32 nPlayers, qint32 maxScore);
    void endRoundAndClear(const std::vector<int>& scr);
    void newDataToWrite(QByteArray);
    void newConnectionInfo(QString ip, qint32 port);
    void newSceneMessage(QString message);

public slots:
    void setWindow(qint32, qint32);
    void newPoint(GamePlay::Point);
    void endRound(const std::vector<int>&);
    void newKeyPressedMessageToSend(Communication::KeyPressedMessage msg);
    void newKeyReleasedMessageToSend(Communication::KeyReleasedMessage msg);
    void generateConnectionInfo();
    void gameOver();

private:
    qreal boardPixelSize;
    AddressDialog ipDialog;
};

#endif // CONTROLLER_H
