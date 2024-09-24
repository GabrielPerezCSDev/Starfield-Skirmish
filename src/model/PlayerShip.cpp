#include "Model/PlayerShip.h"

const char* PlayerShip::PLAYER_SHIP_ART[length] = {
    "<=|=>"
};

void PlayerShip::draw(WINDOW* win) const {
    mvwprintw(win, getY(), getX(), "%s", PLAYER_SHIP_ART[0]);
}

void PlayerShip::shoot() {
    // Implement shooting logic for the player ship
    // This could involve creating a projectile and adding it to the game
}



PlayerShip::PlayerShip(int x, int y) : Ship(x, y, 500) { // Assuming default HP is set here
    setScore(0);
    setFireRate(2.5);
    setFireRateAccumulator(0);
}

std::vector<std::pair<int, int>> PlayerShip::getPlayerCoordinates() const {
    std::vector<std::pair<int, int>> coordinates;
    for (int i = 0; i < getWidthFromStart(); ++i) {
        coordinates.push_back(std::make_pair(x + i, y));
    }
    return coordinates;
}

void PlayerShip::update(double deltaTime) {
    // Decrement the fire rate accumulator every frame
    double newAccumulator = getFireRateAccumulator() - deltaTime;
    setFireRateAccumulator(newAccumulator);

    // Other update logic...
}

 Bullet* PlayerShip::generateBullet(double deltaTime){
    if(canGenerateBullet(deltaTime)){
        Bullet* newBullet = new Bullet(50, 10.0);  // Damage and speed
        newBullet->setX(this->x + (this->getWidthFromStart() / 2));
        newBullet->setY(this->y - 1);
        newBullet->setDesign('|');
        newBullet->setColorPairId(1);
        newBullet->setType(1);
        return newBullet;
    }
        return nullptr;
    
 }

 bool PlayerShip::canGenerateBullet(double deltaTime) {
    if (getFireRateAccumulator() <= 0) {
        setFireRateAccumulator(1.0 / getFireRate());  // Reset accumulator based on fire rate
        return true;
    }
    return false;
}