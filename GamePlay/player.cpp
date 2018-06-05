#include "player.h"
#include "gameplay.h"
#include "board.h"
#include "point.h"
#include <math.h>
#include "gamemode.h"
#include <QDebug>

namespace GamePlay {

Player::Player(int id, double x, double y, double angle) : id(id), score(0), x(x), y(y), angle(angle), radius(GamePlay::defaultRadius), speed(GamePlay::defaultSpeedPerTurn),
                                                           visible(true), squares(false), collisionless(false), rotatingLeft(false), rotatingRight(false), active(true),
                                                           reversed(false)
{

}

Point Player::move(long turn) {
    if(!collisionless) {
        visible = turn&0b110000;
    }
    if(squares) {
        if(rotatingLeft) {
            angle -= M_PI_2;
            cancelRotatingLeft();
        }
        if(rotatingRight) {
            angle += M_PI_2;
            cancelRotatingRight();
        }
    }
    if(rotatingLeft)angle -= GamePlay::defaultAngle;
    if(rotatingRight)angle += GamePlay::defaultAngle;


    x += speed * std::cos(angle);
    y += speed * std::sin(angle);

    return Point(x, y, radius, turn, id, visible);
}

void Player::updateMode(const Bonus& bonus) {

    if(bonus.getMode() == Modes::NORMAL) {
        visible = true;
        collisionless = false;
        squares = false;
        speed = GamePlay::defaultSpeedPerTurn;
        radius = GamePlay::defaultRadius;
        return;
    }

    if(bonus.isActive())
        setMode(bonus.getMode(), bonus.getPlayerID());
    else
        resetMode(bonus.getMode(), bonus.getPlayerID());

}



void Player::setMode(int mode, int playerID) {
    if(mode== Modes::COLLISIONLESS) {
        visible = false;
        collisionless = true;
    }

    if(playerID == id) {
        switch(mode) {
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
        case Modes::REVERSE:
            if(!reversed)std::swap(rotatingLeft, rotatingRight);
            reversed = true;
            break;
        case Modes::SQUARE:
            squares = true;
            break;
        default:
            break;
        }
    }
    else {
        switch(mode) {
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
        case Modes::REVERSE_O:
            if(!reversed)std::swap(rotatingLeft, rotatingRight);
            reversed = true;
            break;
        case Modes::SQUARE_O:
            squares = true;
            break;
        default:
            break;
        }
    }
}

void Player::resetMode(int mode, int playerID) {
    if(mode == Modes::COLLISIONLESS) {
        visible = true;
        collisionless = false;
    }

    if(playerID == id) {
        switch(mode) {
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
        case Modes::REVERSE:
            if(reversed)std::swap(rotatingLeft, rotatingRight);
            reversed = false;
            break;
        case Modes::SQUARE:
            squares = false;
            break;
        default:
            break;
        }
    }
    else {
        switch(mode) {
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
        case Modes::REVERSE_O:
            if(reversed)std::swap(rotatingLeft, rotatingRight);
            reversed = false;
            break;
        case Modes::SQUARE_O:
            squares = false;
            break;
        default:
            break;
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
    if(!reversed)rotatingLeft = true;
    else {
        rotatingRight = true;
    }
}

void Player::setRotatingRight() {
    if(!reversed)rotatingRight = true;
    else {
        rotatingLeft = true;
    }
}

void Player::cancelRotatingLeft() {
    if(!reversed)rotatingLeft = false;
    else {
        rotatingRight = false;
    }
}

void Player::cancelRotatingRight() {
    if(!reversed)rotatingRight = false;
    else {
        rotatingLeft = false;
    }
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

void Player::reset() {
    reversed = false;
    rotatingLeft = false;
    rotatingRight = false;
}
}


