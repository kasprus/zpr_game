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
    connect(&client, SIGNAL(endRound(const std::vector<int>&)), this, SLOT(endRound(const std::vector<int>&)));
    connect(&client, SIGNAL(setWindow(qint32,qint32)), this, SLOT(setWindow(qint32, qint32)));
    connect(this, SIGNAL(newDataToWrite(QByteArray)), &client, SLOT(writeData(QByteArray)));
    connect(&ipDialog, SIGNAL(accepted()), this, SLOT(generateConnectionInfo()));
    connect(this, SIGNAL(newConnectionInfo(QString, qint32)), &client, SLOT(establishConnection(QString, qint32)));
    connect(&client, SIGNAL(gameOver()), this, SLOT(gameOver()));
}

void Controller::setBoardPixelSize(int size) {
    boardPixelSize = size;
}

void Controller::newPoint(GamePlay::Point p) {
    qreal x, y, radius;
    x = (double)boardPixelSize * p.getX() / GamePlay::Board::dimensionX;
    y = (double)boardPixelSize * p.getY() / GamePlay::Board::dimensionY;
    radius = boardPixelSize * p.getRadius() / GamePlay::Board::dimensionX;
    emit newCircle(x, y, 2 * radius, p.getPlayerId());//COLOR
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

void Controller::generateConnectionInfo() {
    emit newConnectionInfo(ipDialog.getIpAddress(), ipDialog.getPortNumber());
}

void Controller::endRound(const std::vector<int>& scr) {
    emit endRoundAndClear(scr);
}

void Controller::setWindow(qint32 nPlayers, qint32 maxScore) {
    emit setWindows(nPlayers, maxScore);
}
void Controller::showIpDialog() {
    ipDialog.show();
}

void Controller::gameOver() {
    emit newSceneMessage("Game over");
}
