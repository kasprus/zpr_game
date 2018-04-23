#ifndef TRANSLATORFROMARRAY_H
#define TRANSLATORFROMARRAY_H

#include <memory>
#include <QByteArray>

namespace Communication {

class Message;

class TranslatorFromArray
{
public:
    TranslatorFromArray();
    std::unique_ptr<Message> getMessage(const QByteArray& ) const;
};

}

#endif // TRANSLATORFROMARRAY_H
