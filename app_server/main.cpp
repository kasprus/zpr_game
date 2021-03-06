#include <stdlib.h>
#include <iostream>
#include <QCoreApplication>

#include "gameserver.h"
#include "parameterselector.h"
#include "parameterexception.h"

int main(int argc, char *argv[])
{
    ParameterSelector selector;
    selector.selectNumberOfPlayer();
    selector.selectNumberOfPoints();
    selector.selectPort();
    std::unique_ptr<GameServer> server;
    try {
        server = std::move(selector.createServer(argc, argv));
    }
    catch(const ParameterException &) {
        std::cerr << "wrong argument values";
        return 0;
    }
    return server->exec();
}

