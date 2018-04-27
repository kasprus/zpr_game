#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <memory>
#include "point.h"
#include "message.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
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
    void newCircle(qreal x, qreal y, qreal radius);
    void newDataToWrite(QByteArray);
    void newIpAddress(QString ip);

public slots:
    void newPoint(GamePlay::Point);
    void newKeyPressedMessageToSend(Communication::KeyPressedMessage msg);
    void newKeyReleasedMessageToSend(Communication::KeyReleasedMessage msg);
    void generateAddressIp();

private:
    qreal boardPixelSize;
    AddressDialog ipDialog;
};

#endif // CONTROLLER_H
