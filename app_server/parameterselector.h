#ifndef PARAMETERSELECTOR_H
#define PARAMETERSELECTOR_H
#include <memory>
#include "gameserver.h"

class ParameterSelector
{
public:
    constexpr static int MIN_PLAYERS = 2;
    constexpr static int MAX_PLAYERS = 6;
    constexpr static int MIN_PORT = 1024;
    constexpr static int MAX_PORT = 65555;
    constexpr static int MIN_POINTS = 5;
    constexpr static int MAX_POINTS = 100;
    ParameterSelector();
    void selectPort();
    void selectNumberOfPlayer();
    void selectNumberOfPoints();
    std::unique_ptr<GameServer> createServer(int argc, char *argv[]);
private:
    void verifyArguments();
    int numberOfPlayers;
    int numberOfPoints;
    int portNumber;
};

#endif // PARAMETERSELECTOR_H
