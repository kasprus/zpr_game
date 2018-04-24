#include "player.h"
#include "gameplay.h"
#include "board.h"
#include "point.h"
#include <math.h>

namespace GamePlay {

Player::Player(int id, double x, double y, double angle) : id(id), x(x), y(y), angle(angle), rotatingLeft(false), rotatingRight(false)
{
}

void Player::move() {
    if(rotatingLeft)angle += GamePlay::defaultAngle;
    if(rotatingRight)angle -= GamePlay::defaultAngle;
    x += GamePlay::defaultSpeedPerTurn * std::cos(angle);
    y += GamePlay::defaultSpeedPerTurn * std::sin(angle);
}

Point Player::getPoint(long turn) const {
    return Point(x, y, GamePlay::defaultRadius, turn, id);
}

void Player::setRotatingLeft() {
    rotatingLeft = true;
}

void Player::setRotatingRight() {
    rotatingRight = true;
}

void Player::cancelRoatingLeft() {
    rotatingLeft = false;
}

void Player::cancelRotatingRight() {
    rotatingRight = false;
}

}


