#include "translatorfromarray.h"
#include "message.h"
#include "bonusmessage.h"
#include "pointmessage.h"
#include "gamestartmessage.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "gameovermessage.h"
#include "gamedelaymessage.h"
#include "communication.h"
#include "point.h"
#include <QDataStream>

namespace Communication {

TranslatorFromArray::TranslatorFromArray()
{

}

std::unique_ptr<Message> TranslatorFromArray::getMessage(const QByteArray& array) const {
    QByteArray tmp(array);
    QDataStream dataStream(&tmp, QIODevice::ReadOnly);
    dataStream.setVersion(QDataStream::Qt_5_0);
    dataStream.setByteOrder(QDataStream::LittleEndian);
    dataStream.setFloatingPointPrecision(QDataStream::DoublePrecision);
    qint32 type;
    dataStream>>type;
    if(type == Communication::Communication::pointMessageHeader) {
        PointMessage *m = new PointMessage;
        qint32 size;
        dataStream>>size;
        while(size > 0) {
            double x, y, radius;
            qint64 turn;
            qint32 player;
            qint8 visible;
            dataStream>>x>>y>>radius>>turn>>player>>visible;
            m->addPoint(GamePlay::Point(x, y, radius, turn, player, visible));
            --size;
        }
        return std::unique_ptr<Message>(m);
    }
    else if(type == Communication::Communication::keyPressedMessageHeader) {
        KeyPressedMessage *m;
        qint32 tmp;
        qint32 key;
        dataStream>>tmp>>key;
        m = new KeyPressedMessage(key);
        return std::unique_ptr<Message>(m);
    }
    else if(type == Communication::Communication::keyReleasedMessageHeader) {
        KeyReleasedMessage *m;
        qint32 tmp;
        qint32 key;
        dataStream>>tmp>>key;
        m = new KeyReleasedMessage(key);
        return std::unique_ptr<Message>(m);
    }
    else if (type == Communication::roundEndMessageHeader) {
        RoundEndMessage *m;
        qint32 tmp;
        qint32 nPlayers;
        qint32 score;

        dataStream >> tmp >> nPlayers;
        m = new RoundEndMessage(nPlayers);
        for(int i = 0; i < nPlayers; ++i) {
            dataStream >> score;
            m->addScore(i, score);
        }

        return std::unique_ptr<Message>(m);
    }
    else if (type == Communication::gameStartMessageHeader) {
        GameStartMessage *m;
        qint32 tmp;
        qint32 nPlayers;
        qint32 maxScore;
        qint32 playerNumber;
        dataStream >> tmp >> nPlayers >> maxScore >> playerNumber;
        m = new GameStartMessage(nPlayers, maxScore, playerNumber);

        return std::unique_ptr<Message>(m);
    }
    else if(type == Communication::gameOverMessageHeader) {
        qint32 winner;
        dataStream>>winner;
        return std::unique_ptr<Message>(new GameOverMessage(winner));
    }
    else if(type == Communication::gameDelayMessageHeader) {
        GameDelayMessage *m;
        qint32 tmp;
        qint32 delay;

        dataStream>>tmp>>delay;
        m = new GameDelayMessage(delay);
        return std::unique_ptr<Message>(m);
    }
    else if(type == Communication::bonusMessageHeader) {
        BonusMessage *m;
        qint32 tmp, mode;
        double x, y;
        qint8 showBonus;
        dataStream >> tmp >> mode >> x >> y >> showBonus;

        m = new BonusMessage(mode, x, y, showBonus);
        return std::unique_ptr<Message>(m);
    }
    return std::unique_ptr<Message>(nullptr);
}

}
