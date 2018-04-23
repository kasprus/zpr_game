#ifndef MESSAGE_H
#define MESSAGE_H

namespace Communication {

class PointMessage;
class TranslatorToArray;

class Message
{
public:
    Message();
    virtual void accept(const TranslatorToArray& translator) = 0;
    virtual int getHeader() = 0;
    virtual ~Message();
};

}

#endif // MESSAGE_H
