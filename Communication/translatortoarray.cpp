#include "translatortoarray.h"
#include "pointmessage.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "communication.h"
#include <QIODevice>
#include <QDataStream>

namespace Communication {

TranslatorToArray::TranslatorToArray()
{

}

void TranslatorToArray::visit(const PointMessage &pointMessage) const{
    lastMessage = QByteArray();
    int usedBytes = 0;
    QDataStream out(&lastMessage, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);
    auto points = pointMessage.getPoints();
    out<<qint32(Communication::pointMessageHeader)<<qint32(points.size());
    usedBytes += Communication::headerSize;
    for(auto &p : points) {
        out<<p.getX()<<p.getY()<<p.getRadius()<<qint64(p.getTurnNumber())<<qint32(p.getPlayerId());
        usedBytes += PointMessage::messageItemSize;
    }
    while(usedBytes < Communication::messageSize) {
        out<<qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const KeyPressedMessage &keyPressedMessage) const {
    lastMessage = QByteArray();
    int usedBytes = 0;
    QDataStream out(&lastMessage, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);
    out<<qint32(keyPressedMessage.getHeader())<<qint32(0)<<qint32(keyPressedMessage.getKeyId());
    usedBytes += Communication::headerSize + 4;
    while(usedBytes < Communication::messageSize) {
        out<<qint8(0);
        ++usedBytes;
    }
}

void TranslatorToArray::visit(const KeyReleasedMessage &keyReleasedMessage) const {
    lastMessage = QByteArray();
    int usedBytes = 0;
    QDataStream out(&lastMessage, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::DoublePrecision);
    out<<qint32(keyReleasedMessage.getHeader())<<qint32(0)<<qint32(keyReleasedMessage.getKeyId());
    usedBytes += Communication::headerSize + 4;
    while(usedBytes < Communication::messageSize) {
        out<<qint8(0);
        ++usedBytes;
    }
}

QByteArray TranslatorToArray::getLastMessage() const {
    return lastMessage;
}

}
