#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

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


class MessageVisitor {
public:
    virtual void visit(const PointMessage& pointMessage) const = 0;
    virtual void visit(const KeyPressedMessage& keyPressedMessage) const = 0;
    virtual void visit(const KeyReleasedMessage& keyReleasedMessage) const = 0;
    virtual void visit(const RoundEndMessage& roundEndMessage) const = 0;
    virtual void visit(const GameStartMessage& gameStartMessage) const = 0;
    virtual void visit(const GameOverMessage& gameOverMessage) const = 0;
    virtual void visit(const GameDelayMessage& gameDelayMessage ) const = 0;
    virtual void visit(const BonusMessage& bonusMessage) const = 0;
    virtual void visit(const GameScoreMessage& gameScoreMessage) const = 0;

};
}



#endif // MESSAGEVISITOR_H
