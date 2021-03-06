#include <QIODevice>
#include <QDataStream>

#include "translatortoarray.h"
#include "bonusmessage.h"
#include "gamestartmessage.h"
#include "pointmessage.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "communication.h"
#include "gameovermessage.h"
#include "gamedelaymessage.h"
#include "gamescoremessage.h"

namespace Communication {

TranslatorToArray::TranslatorToArray()
{

}

void TranslatorToArray::visit(const PointMessage &pointMessage) const{
    int usedBytes = 0;
    auto out = prepareLastMessage();
    auto points = pointMessage.getPoints();
    *out<<qint32(Communication::pointMessageHeader)<<qint32(points.size());
    usedBytes += Communication::headerSize;
    for(auto &p : points) {
        *out<<p.getX()<<p.getY()<<p.getRadius()<<qint64(p.getTurnNumber())<<qint32(p.getPlayerId())<<qint8(p.isVisible());
        usedBytes += PointMessage::messageItemSize;
    }
    while(usedBytes < Communication::messageSize) {
        *out<<qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const KeyPressedMessage &keyPressedMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out<<qint32(keyPressedMessage.getHeader())<<qint32(0)<<qint32(keyPressedMessage.getKeyId());
    usedBytes += Communication::headerSize + 4;
    while(usedBytes < Communication::messageSize) {
        *out<<qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const KeyReleasedMessage &keyReleasedMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out<<qint32(keyReleasedMessage.getHeader())<<qint32(0)<<qint32(keyReleasedMessage.getKeyId());
    usedBytes += Communication::headerSize + 4;
    while(usedBytes < Communication::messageSize) {
        *out<<qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const RoundEndMessage &roundEndMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(roundEndMessage.getHeader()) << qint32(0);
    usedBytes += Communication::headerSize;
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const GameStartMessage &gameStartMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(gameStartMessage.getHeader()) << qint32(0);
    *out << qint32(gameStartMessage.getNumberOfPlayers()) << qint32(gameStartMessage.getMaxScore()) << qint32(gameStartMessage.getPlayerNumber());
    usedBytes += 20;
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const GameOverMessage &gameOverMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(gameOverMessage.getHeader()) << qint32(gameOverMessage.getWinner());
    usedBytes += 8;
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const GameDelayMessage &gameDelayMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(gameDelayMessage.getHeader()) << qint32(0);
    usedBytes += Communication::headerSize;
    *out << qint32(gameDelayMessage.getDelay());
    usedBytes += 4;
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const BonusMessage &bonusMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(bonusMessage.getHeader()) <<qint32(0);
    usedBytes += Communication::headerSize;
    *out << qint32(bonusMessage.getMode());
    *out << bonusMessage.getX() << bonusMessage.getY();
    *out << qint8(bonusMessage.getShowBonus());
    usedBytes += 21;
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const GameScoreMessage& gameScoreMessage) const {
    int usedBytes = 0;
    auto out = prepareLastMessage();
    *out << qint32(gameScoreMessage.getHeader()) << qint32(0);
    usedBytes += Communication::headerSize;
    *out << qint32(gameScoreMessage.getNumberOfPlayers());
    usedBytes +=4;
    for(int score : gameScoreMessage.getScore()) {
        *out << qint32(score);
        usedBytes += 4;
    }
    while(usedBytes < Communication::messageSize) {
        *out << qint8(0);
        ++usedBytes;
    }

}


std::unique_ptr<QDataStream> TranslatorToArray::prepareLastMessage() const {
    lastMessage = QByteArray();
    QDataStream *out = new QDataStream(&lastMessage, QIODevice::WriteOnly);
    out->setVersion(QDataStream::Qt_5_0);
    out->setByteOrder(QDataStream::LittleEndian);
    out->setFloatingPointPrecision(QDataStream::DoublePrecision);
    return std::unique_ptr<QDataStream>(out);
}



QByteArray TranslatorToArray::getLastMessage() const {
    return lastMessage;
}

}
