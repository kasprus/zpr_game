#ifndef COMMUNICATION_H
#define COMMUNICATION_H

namespace Communication {

class Communication
{

public:
    constexpr const static int messageSize = 128;
    constexpr const static int headerSize = 8;
    constexpr const static int pointMessageHeader = 1;
    Communication();
};

}
#endif // COMMUNICATION_H
