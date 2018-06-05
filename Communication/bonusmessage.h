#ifndef BONUSMESSAGE_H
#define BONUSMESSAGE_H

#include "message.h"
#include "gamemode.h"
#include "bonus.h"

namespace Communication {

class TranslatorToArray;
class Message;
class MessageVisitor;

class BonusMessage : public Message
{
public:
    BonusMessage(int mode, double x, double y, bool showBonus);
    BonusMessage(const GamePlay::Bonus& bonus, bool showBonus);
    virtual int getHeader() const;
    virtual void accept(const MessageVisitor& translator);
    double getX() const;
    double getY() const;
    int getMode() const;
    bool getShowBonus() const;
    virtual ~BonusMessage();
private:
    int mode;
    double x, y;
    bool showBonus; // true to show, false to erase from board
};


}
#endif // BONUSMESSAGE_H
