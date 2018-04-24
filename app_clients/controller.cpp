#include <QObject>
#include <QDebug>
#include "controller.h"
#include "gameclient.h"
#include "gameplay.h"
#include "board.h"
#include "translatortoarray.h"

Controller::Controller(GameClient &client, QObject *parent) : QObject(parent), boardPixelSize(0)
{
    connect(&client, SIGNAL(newPoint(GamePlay::Point)), this, SLOT(newPoint(GamePlay::Point)));
    connect(this, SIGNAL(newDataToWrite(QByteArray)), &client, SLOT(writeData(QByteArray)));
}

void Controller::setBoardPixelSize(int size) {
    boardPixelSize = size;
}

void Controller::newPoint(GamePlay::Point p) {
    qreal x, y, radius;
    x = (double)boardPixelSize * p.getX() / GamePlay::Board::dimensionX;
    y = (double)boardPixelSize * p.getY() / GamePlay::Board::dimensionY;
    radius = boardPixelSize * p.getRadius() / GamePlay::Board::dimensionX;
//    qDebug()<<x<<" "<<y<<" "<<radius;
    QGraphicsItem *item = new QGraphicsEllipseItem(x, y, radius, radius);
    item->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    emit newItem(item);
}

void Controller::newKeyPressedMessageToSend(Communication::KeyPressedMessage msg) {
    Communication::TranslatorToArray translator;
    msg.accept(translator);
    emit newDataToWrite(translator.getLastMessage());
}

void Controller::newKeyReleasedMessageToSend(Communication::KeyReleasedMessage msg) {
    Communication::TranslatorToArray translator;
    msg.accept(translator);
    emit newDataToWrite(translator.getLastMessage());
}
