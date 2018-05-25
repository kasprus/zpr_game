#ifndef PARAMETERSELECTOR_H
#define PARAMETERSELECTOR_H
#include <memory>
#include "gameserver.h"

class ParameterSelector
{
public:
    constexpr static int MIN_PLAYERS = 1;
    constexpr static int MAX_PLAYERS = 6;
    constexpr static int MIN_PORT = 1024;
    constexpr static int MAX_PORT = 65535;
    constexpr static int MIN_POINTS = 1;
    constexpr static int MAX_POINTS = 100;
    constexpr static int DEFAULT_PLAYERS = 2;
    constexpr static int DEFAULT_POINTS = 5;
    constexpr static int DEFAULT_PORT = 4321;
    ParameterSelector();
    void selectPort();
    void selectNumberOfPlayer();
    void selectNumberOfPoints();
    std::unique_ptr<GameServer> createServer(int argc, char *argv[]);
private:
    int getParametersFromStdInput(int defaultValue) const;
    void verifyArguments();
    int numberOfPlayers;
    int numberOfPoints;
    int portNumber;
};

#endif // PARAMETERSELECTOR_H
