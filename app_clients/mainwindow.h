#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <memory>
#include "communication.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"

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
    void newItem(QGraphicsItem* ptr);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
