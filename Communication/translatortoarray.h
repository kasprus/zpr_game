#ifndef TRANSLATORTOARRAY_H
#define TRANSLATORTOARRAY_H

#include <QByteArray>
#include <QDataStream>
#include <memory>

#include "messagevisitor.h"

namespace Communication {

class PointMessage;
class KeyPressedMessage;
class KeyReleasedMessage;
class RoundEndMessage;
class GameStartMessage;
class GameOverMessage;
class GameDelayMessage;
class BonusMessage;
class GameScoreMessage;


class TranslatorToArray : public MessageVisitor
{
public:
    TranslatorToArray();
    virtual void visit(const PointMessage &pointMessage) const;
    virtual void visit(const KeyPressedMessage &keyPressedMessage) const;
    virtual void visit(const KeyReleasedMessage &keyReleasedMessage) const;
    virtual void visit(const RoundEndMessage &roundEndMessage) const;
    virtual void visit(const GameStartMessage& gameStartMessage) const;
    virtual void visit(const GameOverMessage& gameOverMessage) const;
    virtual void visit(const GameDelayMessage &gameDelayMessage) const;
    virtual void visit(const BonusMessage& bonusMessage) const;
    virtual void visit(const GameScoreMessage& gameScoreMessage) const;

    QByteArray getLastMessage() const;
private:
    std::unique_ptr<QDataStream> prepareLastMessage() const;
    mutable QByteArray lastMessage;
};

}

#endif // TRANSLATORTOARRAY_H
