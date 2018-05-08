#include <iostream>
#include "parameterselector.h"
#include "parameterexception.h"

ParameterSelector::ParameterSelector() : numberOfPlayers(0), numberOfPoints(0), portNumber(0)
{

}

void ParameterSelector::selectNumberOfPlayer() {
    std::cout<<"Select number of players ["<<MIN_PLAYERS<<" : "<<MAX_PLAYERS<<"]\n";
    std::cin>>numberOfPlayers;
}

void ParameterSelector::selectNumberOfPoints() {
    std::cout<<"Select number of points ["<<MIN_POINTS<<" : "<<MAX_POINTS<<"]\n";
    std::cin>>numberOfPoints;
}

void ParameterSelector::selectPort() {
    std::cout<<"Select port number ["<<MIN_PORT<<" : "<<MAX_PORT<<"]\n";
    std::cin>>portNumber;
}

void ParameterSelector::verifyArguments() {
    if(numberOfPlayers < MIN_PLAYERS ||
    numberOfPlayers > MAX_PLAYERS ||
    numberOfPoints < MIN_POINTS ||
    numberOfPoints > MAX_POINTS ||
    portNumber < MIN_PORT ||
    portNumber > MAX_PORT)throw ParameterException();
}

std::unique_ptr<GameServer> ParameterSelector::createServer(int argc, char *argv[]) {
    verifyArguments();
    return std::unique_ptr<GameServer>(new GameServer(argc, argv, numberOfPlayers, numberOfPoints, portNumber));
}

