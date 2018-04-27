#include <QCoreApplication>
#include <gameserver.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc < 2) {
        qDebug()<<"Used default number of players: 2";
        GameServer server(2);
        return a.exec();
    } else {
        GameServer server(atoi(argv[1]));
        return a.exec();
    }
}

