#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace Communication {

class Communication
{

public:
    constexpr static int messageSize = 128;
    constexpr static int headerSize = 8;
    constexpr static int pointMessageHeader = 1;
    constexpr static int keyPressedMessageHeader = 2;
    constexpr static int keyReleasedMessageHeader = 3;
    constexpr static int roundEndMessageHeader = 4;
    constexpr static int gameStartMessageHeader = 5;
    constexpr static int gameOverMessageHeader = 6;
    constexpr static int gameDelayMessageHeader = 7;
    constexpr static int bonusMessageHeader = 8;
    constexpr static int gameScoreMessageHeader = 9;

    constexpr static int leftKeyId = 0;
    constexpr static int rightKeyId = 1;
private:
    Communication();
};

}
#endif // COMMUNICATION_H
