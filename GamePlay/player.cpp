#include "player.h"
#include "gameplay.h"
#include "board.h"
#include "point.h"
#include <math.h>
#include "gamemode.h"
#include <QDebug>

namespace GamePlay {

Player::Player(int id, double x, double y, double angle) : id(id), score(0), x(x), y(y), angle(angle), radius(GamePlay::defaultRadius), speed(GamePlay::defaultSpeedPerTurn),
                                                           visible(true), squares(false), collisionless(false), rotatingLeft(false), rotatingRight(false), active(true)
{

}

Point Player::move(long turn) {
    if(!collisionless) {
        visible = turn&0b110000;
    }
    if(angle) {


    }
    if(rotatingLeft)angle -= GamePlay::defaultAngle;
    if(rotatingRight)angle += GamePlay::defaultAngle;
    x += speed * std::cos(angle);
    y += speed * std::sin(angle);

    return Point(x, y, radius, turn, id, visible);
}

void Player::updateMode(const Bonus& bonus) {
    //TODO: add states to bonus, refactor
    //qDebug() << bonus.getMode() << bonus.getPlayerID();
    if(bonus.getMode() == Modes::NORMAL) {
        visible = true;
        collisionless = false;
        speed = GamePlay::defaultSpeedPerTurn;
        radius = GamePlay::defaultRadius;
        return;
    }
    if(bonus.isActive()) {
        if(bonus.getMode() == Modes::COLLISIONLESS) {
            visible = false;
            collisionless = true;
        }

        if(bonus.getPlayerID() == id) {
            switch(bonus.getMode()) {
            case Modes::THICK:
                radius = GamePlay::bigRadius;
                break;
            case Modes::THIN:
                radius = GamePlay::smallRadius;
                break;
            case Modes::FAST:
                speed = GamePlay::fastSpeedPerTurn;
                break;
            case Modes::SLOW:
                speed = GamePlay::slowSpeedPerTurn;
                break;
            default:
                break;
            }
        }
        else {
            switch(bonus.getMode()) {
            case Modes::THICK_O:
                radius = GamePlay::bigRadius;
                break;
            case Modes::THIN_O:
                radius = GamePlay::smallRadius;
                break;
            case Modes::FAST_O:
                speed = GamePlay::fastSpeedPerTurn;
                break;
            case Modes::SLOW_O:
                speed = GamePlay::slowSpeedPerTurn;
                break;
            default:
                break;
            }
        }


    }
    else {
        if(bonus.getMode() == Modes::COLLISIONLESS) {
            visible = true;
            collisionless = false;
        }

        if(bonus.getPlayerID() == id) {
            switch(bonus.getMode()) {
            case Modes::THICK:
                /* fall through */
            case Modes::THIN:
                radius = GamePlay::defaultRadius;
                break;
            case Modes::FAST:
                /* fall through */
            case Modes::SLOW:
                speed = GamePlay::defaultSpeedPerTurn;
                break;
            default:
                break;
            }
        }
        else {
            switch(bonus.getMode()) {
            case Modes::THICK_O:
                /* fall through */
            case Modes::THIN_O:
                radius = GamePlay::defaultRadius;
                break;
            case Modes::FAST_O:
                /* fall through */
            case Modes::SLOW_O:
                speed = GamePlay::defaultSpeedPerTurn;
                break;
            default:
                break;
            }
        }
    }
}

void Player::setCoordinatesAndAngle(double x_, double y_, double angle_) {
    x = x_;
    y = y_;
    angle = angle_;
}

Point Player::getPoint(long turn) const {
    return Point(x, y, GamePlay::defaultRadius, turn, id, turn);
}
void Player::addScore(int pts) {
    score += pts;
}
void Player::setRotatingLeft() {
    rotatingLeft = true;
}

void Player::setRotatingRight() {
    rotatingRight = true;
}

void Player::cancelRotatingLeft() {
    rotatingLeft = false;
}

void Player::cancelRotatingRight() {
    rotatingRight = false;
}

bool Player::isActive() const {
    return active;
}

void Player::setActive() {
    active = true;
}
void Player::setInactive() {
    active = false;
}
}


