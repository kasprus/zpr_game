#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <memory>
#include <string>
#include <vector>
#include <QPen>
#include <QLabel>
#include "communication.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "addressdialog.h"

namespace Ui {
class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller &controller, QWidget *parent = 0);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    ~MainWindow();

signals:
    void newKeyPressedMessage(Communication::KeyPressedMessage msg);
    void newKeyReleasedMessage(Communication::KeyReleasedMessage msg);


private slots:
    void newCircle(qreal x, qreal y, qreal radius, qint32 pID, bool isVisible);
    void endRoundAndClear(const std::vector<int>& scr);
    void setWindows(qint32 playersCount, qint32 maxScore);
    void printSceneMessage(QString message);
private:
    QLabel sceneMessage;
    Ui::MainWindow *ui;
    void setScores(const std::vector<int>& scr);
    void clearBoard(int sz);
    std::vector<QGraphicsEllipseItem*> invisiblePoints;
    int nPlayers;
    const int colors[6] = {0xfd0000, 0x00edc5, 0x0eed00, 0xeddb00, 0xed00c5, 0xd8e7e1 };
    const std::string colorsName[6] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "WHITE"};
};

#endif // MAINWINDOW_H
