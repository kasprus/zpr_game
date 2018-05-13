#include "player.h"
#include "gameplay.h"
#include "board.h"
#include "point.h"
#include <math.h>
#include "gamemode.h"


namespace GamePlay {

Player::Player(int id, double x, double y, double angle) : id(id), score(0), x(x), y(y), angle(angle), radius(GamePlay::defaultRadius), speed(GamePlay::defaultSpeedPerTurn),
                                                           visible(true), squares(false), collisionless(false), rotatingLeft(false), rotatingRight(false), active(true)
{

}

Point Player::move(long turn) {
    if(!collisionless) {
        visible = turn&0b110000;
    }
    if(rotatingLeft)angle -= GamePlay::defaultAngle;
    if(rotatingRight)angle += GamePlay::defaultAngle;
    x += speed * std::cos(angle);
    y += speed * std::sin(angle);

    return Point(x, y, radius, turn, id, visible);
}

void Player::updateMode(Mode mode, int pID) {
    ++pID;
    speed = GamePlay::defaultSpeedPerTurn;
    radius = GamePlay::defaultRadius;
    visible = true;




    switch(mode) {
    case Mode::COLLISIONLESS:
        visible = false;
        collisionless = true;
        break;
    case Mode::THICK:
        radius = GamePlay::bigRadius;
        speed = GamePlay::defaultSpeedPerTurn;
        break;
    case Mode::THIN:
        radius = GamePlay::smallRadius;
        speed = GamePlay::defaultSpeedPerTurn;
        break;
    case Mode::FAST:
        speed = GamePlay::fastSpeedPerTurn;
        radius = GamePlay::defaultRadius;
        break;
    case Mode::SLOW:
        speed = GamePlay::slowSpeedPerTurn;
        radius = GamePlay::defaultRadius;
        break;
    default:
        break;
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


