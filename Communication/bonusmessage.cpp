#include "message.h"
#include "bonusmessage.h"
#include "translatortoarray.h"
#include "communication.h"
#include "gamemode.h"

namespace Communication {

BonusMessage::BonusMessage(int mode, double x, double y, bool showBonus) : mode(mode), x(x), y(y), showBonus(showBonus)
{
}
BonusMessage::BonusMessage(const GamePlay::Bonus& bonus, bool showBonus) : mode(bonus.getMode()), x(bonus.getX()), y(bonus.getY()), showBonus(showBonus)
{
}
void BonusMessage::accept(const TranslatorToArray& translator) {
    translator.visit(*this);
}

int BonusMessage::getHeader() const {
    return Communication::Communication::bonusMessageHeader;
}

double BonusMessage::getX() const {
    return x;
}

double BonusMessage::getY() const {
    return y;
}

int BonusMessage::getMode() const {
    return mode;
}

bool BonusMessage::getShowBonus() const {
    return showBonus;
}
BonusMessage::~BonusMessage()
{

}
}
