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
    connect(&client, SIGNAL(gameDelay(qint32)), this, SLOT(gameDelay(qint32)));
    connect(&client, SIGNAL(newConnectionMessage(bool)), this, SLOT(newConnection(bool)));
}

void Controller::setBoardPixelSize(int size) {
    boardPixelSize = size;
}

void Controller::newPoint(GamePlay::Point p) {
    qreal x, y, radius;
    x = (double)boardPixelSize * p.getX() / GamePlay::Board::dimensionX;
    y = (double)boardPixelSize * p.getY() / GamePlay::Board::dimensionY;
    radius = boardPixelSize * p.getRadius() / GamePlay::Board::dimensionX;

    emit newCircle(x, y, 2 * radius, p.getPlayerId(), p.isVisible());//COLOR
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
    qDebug() << "CONTROLLER END ROUND";
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

void Controller::gameDelay(qint32 delay) {
    qDebug() << "Control delay: "<<QString::number(delay);
    if(delay > 0)emit newSceneMessage("Game starts in " + QString::number(delay) + " seconds");
    else {
        emit clearMessages();
    }
}

void Controller::newConnection(bool status) {
    if(status) {
        emit newSceneMessage("Waiting for ");
    }
    else {
        emit newSceneMessage("Cannot connect to server");
    }
}
