#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace Communication {

class Communication
{

public:
    constexpr const static int messageSize = 128;
    constexpr const static int headerSize = 8;
    constexpr const static int pointMessageHeader = 1;
    constexpr const static int keyPressedMessageHeader = 2;
    constexpr const static int keyReleasedMessageHeader = 3;


    constexpr const static int leftKeyId = 0;
    constexpr const static int rightKeyId = 1;
    Communication();
};

}
#endif // COMMUNICATION_H
