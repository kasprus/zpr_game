#include "mainwindow.h"
#include "gameclient.h"
#include "controller.h"
#include <QApplication>

/**
 * @brief Main game client function
 * @param argc
 * @param argv
 * @return 0 if no errot
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameClient clinet;
    Controller controller(clinet);
    MainWindow w(controller);
    w.show();
    controller.showIpDialog();

    return a.exec();
}
