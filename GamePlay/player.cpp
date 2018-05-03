#include "player.h"
#include "gameplay.h"
#include "board.h"
#include "point.h"
#include <math.h>

namespace GamePlay {

Player::Player(int id, double x, double y, double angle) : id(id), score(0), x(x), y(y), angle(angle), rotatingLeft(false), rotatingRight(false), active(true)
{
}

void Player::move() {
    if(rotatingLeft)angle -= GamePlay::defaultAngle;
    if(rotatingRight)angle += GamePlay::defaultAngle;
    x += GamePlay::defaultSpeedPerTurn * std::cos(angle);
    y += GamePlay::defaultSpeedPerTurn * std::sin(angle);
}

void Player::setCoordinatesAndAngle(double x_, double y_, double angle_) {
    x = x_;
    y = y_;
    angle = angle_;
}

Point Player::getPoint(long turn) const {
    return Point(x, y, GamePlay::defaultRadius, turn, id);
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


