#ifndef BONUS_H
#define BONUS_H

#include <chrono>
namespace GamePlay {

class Bonus {
public:
    Bonus(int mode, int playerID = -1, std::chrono::system_clock::time_point timeout = std::chrono::system_clock::now(), double x = -1, double y = -1);
    //Bonus(const Bonus& bonus);
    int getMode() const;
    int getPlayerID() const;
    double getX() const;
    double getY() const;
    bool isActive() const;
    void setActive(int pID);
    void setInactive();
    std::chrono::system_clock::time_point getTimeout() const;


private:
    int mode;
    int playerID;
    bool active;
    std::chrono::system_clock::time_point timeout;
    double x, y;
};

}
#endif // BONUS_H
