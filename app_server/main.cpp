#include <QCoreApplication>
#include <gameserver.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer server(2);
    return a.exec();
}

