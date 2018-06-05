#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QLabel>

#include "communication.h"
#include "keypressedmessage.h"
#include "keyreleasedmessage.h"
#include "roundendmessage.h"
#include "addressdialog.h"
#include "modes.h"
#include "gameplay.h"

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
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
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

    /**
     * @brief Called on enter key
     */
    void accept();


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
    void endRoundAndClear();

    /**
     * @brief Sets meta game information
     * @param playersCount number of players
     * @param maxScore maximum number of scores
     */
    void setScoreBoard(qint32 playersCount, qint32 maxScore, qint32 playerNumber);

    /**
     * @brief Prints message on the scene
     * @param message Message o print
     */
    void printSceneMessage(QString message);

    /**
     * @brief Hides mesage on scene.
     */

    void hideSceneMessage();

    /**
     * @brief Displays new bonus on board.
     * @param mode Bonus type
     * @param x
     * @param y
     */
    void showBonus(qint32 mode, qreal x, qreal y);

    /**
     * @brief hideBonus Hides bonus from board.
     * @param mode mode of bonus to hide.
     */
    void hideBonus(qint32 mode);

    void updateScore(const std::vector<int> scores);

    /**
     * @brief Returns player colors used by window
     * @return vector of strings with color names
     */
    const std::vector<std::string> getColorNames() const;

private:
    QLabel sceneMessage;
    Ui::MainWindow *ui;
    void setScores(const std::vector<int>& scr);
    void clearBoard();
    std::vector<QGraphicsEllipseItem*> invisiblePoints;
    std::vector<QGraphicsPixmapItem*> bonusItems;
    int nPlayers;
    const std::array<int, GamePlay::GamePlay::maximumNumberOfPlayers> colors = {{0xfd0000, 0x00edc5, 0x0eed00, 0xeddb00, 0xed00c5, 0xd8e7e1 }};
    const std::vector<std::string>colorsName = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "WHITE"};
};

#endif // MAINWINDOW_H
