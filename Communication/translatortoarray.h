#ifndef TRANSLATORTOARRAY_H
#define TRANSLATORTOARRAY_H

#include <QByteArray>

namespace Communication {

class PointMessage;

class TranslatorToArray
{
public:
    TranslatorToArray();
    void visit(const PointMessage &pointMessage) const;
    QByteArray getLastMessage() const;
private:
    mutable QByteArray lastMessage;
};

}

#endif // TRANSLATORTOARRAY_H
