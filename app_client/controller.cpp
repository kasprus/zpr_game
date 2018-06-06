#include <QObject>
#include <iostream>

#include "controller.h"
#include "gameclient.h"
#include "gameplay.h"
#include "board.h"
#include "translatortoarray.h"
#include "messagevisitor.h"
#include "pointmessage.h"
#include "bonusmessage.h"
#include "gamedelaymessage.h"
#include "roundendmessage.h"
#include "gamestartmessage.h"
#include "gameovermessage.h"
#include "gamescoremessage.h"

Controller::Controller(GameClient &client, QObject *parent) : QObject(parent), boardPixelSize(0), acceptReconnect(false), hardReconnect(false)
{
    connect(this, SIGNAL(newDataToWrite(QByteArray)), &client, SLOT(writeData(QByteArray)));
    connect(&ipDialog, SIGNAL(accepted()), this, SLOT(generateConnectionInfo()));
    connect(this, SIGNAL(newConnectionInfo(QString, qint32)), &client, SLOT(establishConnection(QString, qint32)));
    connect(&client, SIGNAL(newConnectionMessage(bool)), this, SLOT(newConnection(bool)));
    connect(this, SIGNAL(reconnect()), &client, SLOT(reconnect()));
}

void Controller::setBoardPixelSize(int size) {
    boardPixelSize = size;
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


void Controller::showIpDialog() {
    ipDialog.show();
}


void Controller::newConnection(bool status) {
    if(status) {
        emit newSceneMessage("Waiting for other players");
    }
    else {
        hardReconnect = true;
        acceptReconnect = true;
        emit newSceneMessage("Cannot connect to server\n Press SPACE to reconnect");
    }
}

void Controller::setColors(std::vector<std::string> colors) {
    colorNames = colors;
}


void Controller::visit(const Communication::PointMessage &pointMessage) const{

    qreal x, y, radius, pID, isVis;

    auto points = pointMessage.getPoints();
    for(auto &p : points) {
        x = (double)boardPixelSize * p.getX() / GamePlay::Board::dimensionX;
        y = (double)boardPixelSize * p.getY() / GamePlay::Board::dimensionY;
        radius = boardPixelSize * p.getRadius() / GamePlay::Board::dimensionX;
        pID = p.getPlayerId(); isVis = p.isVisible();
        emit newCircle(x,y, 2*radius, pID, isVis);
    }
}

void Controller::visit(const Communication::KeyPressedMessage &keyPressedMessage) const {
    (void)keyPressedMessage;
}

void Controller::visit(const Communication::KeyReleasedMessage &keyReleasedMessage) const {
    (void)keyReleasedMessage;
}

void Controller::visit(const Communication::RoundEndMessage &roundEndMessage) const {
    (void)roundEndMessage;
    emit endRoundAndClear();
}

void Controller::visit(const Communication::GameStartMessage &gameStartMessage) const {
    qint32 nPlayers = gameStartMessage.getNumberOfPlayers();
    qint32 maxScore = gameStartMessage.getMaxScore();
    qint32 playerNumber = gameStartMessage.getPlayerNumber();
    emit setScoreBoard(nPlayers, maxScore, playerNumber);
}

void Controller::visit(const Communication::GameOverMessage &gameOverMessage) const {
    acceptReconnect = true;
    emit newSceneMessage(QString::fromStdString(std::string("Game over\n The winner is " + colorNames[gameOverMessage.getWinner()] + "\n Press SPACE to play again")));
}

void Controller::visit(const Communication::GameDelayMessage &gameDelayMessage) const {
    qint32 delay = gameDelayMessage.getDelay();
    if(delay > 0)
        emit newSceneMessage("Game starts in " + QString::number(delay) + " seconds");
    else {
        emit clearMessages();
    }
}

void Controller::visit(const Communication::BonusMessage &bonusMessage) const {
    qreal x = (double)boardPixelSize * bonusMessage.getX() / GamePlay::Board::dimensionX;
    qreal y = (double)boardPixelSize * bonusMessage.getY() / GamePlay::Board::dimensionY;
    qint32 mode = bonusMessage.getMode();
    if(bonusMessage.getShowBonus())
        emit showBonus(mode, x, y);
    else
        emit hideBonus(mode);
}

void Controller::visit(const Communication::GameScoreMessage& gameScoreMessage) const {
    emit updateScore(gameScoreMessage.getScore());
}

void Controller::checkReconnect() {
    if(acceptReconnect) {
        if(hardReconnect) {
            showIpDialog();
        } else {
            emit reconnect();
        }
    }
    hardReconnect = false;
    acceptReconnect = false;
}
