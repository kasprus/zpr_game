#include <iostream>
#include <sstream>
#include "parameterselector.h"
#include "parameterexception.h"

ParameterSelector::ParameterSelector() : numberOfPlayers(0), numberOfPoints(0), portNumber(0)
{

}

void ParameterSelector::selectNumberOfPlayer() {
    std::cout<<"Select number of players ["<<MIN_PLAYERS<<" : "<<MAX_PLAYERS<<"] default is "<<DEFAULT_PLAYERS<<"\n";
    numberOfPlayers = getParametersFromStdInput(DEFAULT_PLAYERS);
}

void ParameterSelector::selectNumberOfPoints() {
    std::cout<<"Select number of points ["<<MIN_POINTS<<" : "<<MAX_POINTS<<"] deafult is "<< DEFAULT_POINTS <<"\n";
    numberOfPoints = getParametersFromStdInput(DEFAULT_POINTS);
}

void ParameterSelector::selectPort() {
    std::cout<<"Select port number ["<<MIN_PORT<<" : "<<MAX_PORT<<"] default is "<<DEFAULT_PORT<<"\n";
    portNumber = getParametersFromStdInput(DEFAULT_PORT);
}

void ParameterSelector::verifyArguments() {
    if(numberOfPlayers < MIN_PLAYERS ||
    numberOfPlayers > MAX_PLAYERS ||
    numberOfPoints < MIN_POINTS ||
    numberOfPoints > MAX_POINTS ||
    portNumber < MIN_PORT ||
    portNumber > MAX_PORT)throw ParameterException();
}

int ParameterSelector::getParametersFromStdInput(int defaultValue) const {
    std::string line;
    std::getline(std::cin, line);
    if(line.size() > 0) {
        int ret;
        std::stringstream(line)>>ret;
        return ret;
    }
    else {
        return defaultValue;
    }
}

std::unique_ptr<GameServer> ParameterSelector::createServer(int argc, char *argv[]) {
    verifyArguments();
    return std::unique_ptr<GameServer>(new GameServer(argc, argv, numberOfPlayers, numberOfPoints, portNumber));
}

