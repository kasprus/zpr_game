#include "translatortoarray.h"
#include "pointmessage.h"
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

QByteArray TranslatorToArray::getLastMessage() const {
    return lastMessage;
}

}
