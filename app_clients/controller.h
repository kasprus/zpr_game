#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsItem>
#include <memory>
#include "point.h"
#include "message.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"

class GameClient;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(GameClient& client, QObject *parent = 0);
    void setBoardPixelSize(int size);
signals:
    void newItem(QGraphicsItem*);
    void newDataToWrite(QByteArray);

public slots:
    void newPoint(GamePlay::Point);
    void newKeyPressedMessageToSend(Communication::KeyPressedMessage msg);
    void newKeyReleasedMessageToSend(Communication::KeyReleasedMessage msg);

private:
    qreal boardPixelSize;


};

#endif // CONTROLLER_H
