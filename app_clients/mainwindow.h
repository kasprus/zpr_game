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

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Contructs whole game window
     * @param controller Controller
     * @param parent Parent - optional
     */
    explicit MainWindow(Controller &controller, QWidget *parent = 0);
    ~MainWindow();

signals:
    /**
     * @brief Called when user presses keyboard key.
     * @param msg Message with information about pressed key.
     */
    void newKeyPressedMessage(Communication::KeyPressedMessage msg);

    /**
     * @brief Called when user releases keyboard key.
     * @param msg Message whit information about released key.
     */
    void newKeyReleasedMessage(Communication::KeyReleasedMessage msg);


private slots:
    /**
     * @brief Draws new circle on board.
     * @param x
     * @param y
     * @param radius
     * @param pId Player number
     * @param isVisible True if point is visible
     */
    void newCircle(qreal x, qreal y, qreal radius, qint32 pID, bool isVisible);

    /**
     * @brief Updates meta game information and clears scene.
     * @param scr Players points
     */
    void endRoundAndClear(const std::vector<int>& scr);

    /**
     * @brief Sets meta game information
     * @param playersCount number of players
     * @param maxScore maximum number of scores
     */
    void setWindows(qint32 playersCount, qint32 maxScore);

    /**
     * @brief Prints message on the scene
     * @param message Message o print
     */
    void printSceneMessage(QString message);

    /**
     * @brief Hides mesage on scene.
     */
    void hideSceneMessage();

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
