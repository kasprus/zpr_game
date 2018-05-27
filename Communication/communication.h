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
    constexpr const static int roundEndMessageHeader = 4;
    constexpr const static int gameStartMessageHeader = 5;
    constexpr const static int gameOverMessageHeader = 6;
    constexpr const static int gameDelayMessageHeader = 7;
    constexpr const static int bonusMessageHeader = 8;

    constexpr const static int leftKeyId = 0;
    constexpr const static int rightKeyId = 1;
private:
    Communication();
};

}
#endif // COMMUNICATION_H
