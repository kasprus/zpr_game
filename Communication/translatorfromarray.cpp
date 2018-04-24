#include "translatorfromarray.h"
#include "message.h"
#include "pointmessage.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "communication.h"
#include "../GamePlay/point.h"
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
            dataStream>>x>>y>>radius>>turn>>player;
            m->addPoint(GamePlay::Point(x, y, radius, turn, player));
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
    return std::unique_ptr<Message>(nullptr);
}

}
