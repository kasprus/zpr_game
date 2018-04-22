#include "mainwindow.h"
#include "gameclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameClient g;
    w.show();

    return a.exec();
}
