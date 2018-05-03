#ifndef TRANSLATORTOARRAY_H
#define TRANSLATORTOARRAY_H

#include <QByteArray>

namespace Communication {

class PointMessage;
class KeyPressedMessage;
class KeyReleasedMessage;
class RoundEndMessage;
class GameStartMessage;
class TranslatorToArray
{
public:
    TranslatorToArray();
    void visit(const PointMessage &pointMessage) const;
    void visit(const KeyPressedMessage &keyPressedMessage) const;
    void visit(const KeyReleasedMessage &keyPressedMessage) const;
    void visit(const RoundEndMessage &roundEndMessage) const;
    void visit(const GameStartMessage& gameStartMessage) const;
    QByteArray getLastMessage() const;
private:
    mutable QByteArray lastMessage;
};

}

#endif // TRANSLATORTOARRAY_H
