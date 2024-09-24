// AlienShip.cpp
#include "Model/AlienShip.h"
#include "Model/FastAlienShip.h"
#include "Model/TankAlienShip.h"
#include "Model/Utility.h"


std::unique_ptr<AlienShip> AlienShip::createShip(const std::string& type, int x, int y) {
    if (type == "Fast") {
        return std::make_unique<FastAlienShip>(x, y);
    } else if (type == "Tank") {
        return std::make_unique<TankAlienShip>(x, y);
    }
    return nullptr;
}

void AlienShip::update(double deltaTime) {
    moveAccumulator -= deltaTime;
    while (moveAccumulator <= 0) {
        if (direc == 'e') {
            x += 1;  // Move east
        } else if (direc== 'w') {
            x -= 1;  // Move west
        }
        moveAccumulator += 1.0 / getSpeed();  // Reset accumulator based on speed
    }
}


void AlienShip::updateAcum(double deltaTime){
    // Decrement the fire rate accumulator every frame
    double newAccumulator = getFireRateAccumulator() - deltaTime;
    setFireRateAccumulator(newAccumulator);
}

bool AlienShip::canGenerateBullet(double deltaTime) {
    if (getFireRateAccumulator() <= 0) {
        setFireRateAccumulator(1.0 / getFireRate());  // Reset accumulator based on fire rate
        return true;
    }
    return false;
}
/*
int AlienShip::getHp() const { return hp; }
void AlienShip::setHp(int hp) { this->hp = hp; }
double AlienShip::getSpeed() const { return speed; }
void AlienShip::setSpeed(double speed) { this->speed = speed; }
int AlienShip::getX() const { return x; }
void AlienShip::setX(int x) { this->x = x; }
int AlienShip::getY() const { return y; }
void AlienShip::setY(int y) { this->y = y; }

void AlienShip::setDirec(char c) {this->direc = c;}
char AlienShip::getDirec() const {return this->direc;}
*/