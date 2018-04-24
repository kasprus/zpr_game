#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <memory>

namespace Ui {
class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller &controller, QWidget *parent = 0);
//    virtual void keyPressEvent(QEvent *event);
//    virtual void keyReleaseEvent(QEvent *event);
    ~MainWindow();

signals:

private slots:
    void newItem(QGraphicsItem* ptr);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
