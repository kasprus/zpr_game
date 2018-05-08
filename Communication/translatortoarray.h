#ifndef TRANSLATORTOARRAY_H
#define TRANSLATORTOARRAY_H

#include <QByteArray>
#include <QDataStream>
#include <memory>

namespace Communication {

class PointMessage;
class KeyPressedMessage;
class KeyReleasedMessage;
class RoundEndMessage;
class GameStartMessage;
class GameOverMessage;
class TranslatorToArray
{
public:
    TranslatorToArray();
    void visit(const PointMessage &pointMessage) const;
    void visit(const KeyPressedMessage &keyPressedMessage) const;
    void visit(const KeyReleasedMessage &keyPressedMessage) const;
    void visit(const RoundEndMessage &roundEndMessage) const;
    void visit(const GameStartMessage& gameStartMessage) const;
    void visit(const GameOverMessage& gameOverMessage) const;
    QByteArray getLastMessage() const;
private:
    std::unique_ptr<QDataStream> prepareLatMessage() const;
    mutable QByteArray lastMessage;
};

}

#endif // TRANSLATORTOARRAY_H
