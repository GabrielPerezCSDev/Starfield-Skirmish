// TankAlienShip.cpp
#include "Model/TankAlienShip.h"
#include <cstring> // Include for strlen

TankAlienShip::TankAlienShip(int x, int y) : AlienShip(x, y, 100) {  // Pass only x, y, and hp to the base constructor
    speed = 3.0;  // Set the specific speed for FastAlienShip
    setFireRateAccumulator(0.0);
    setFireRate(0.3);
    setMaxHp(100);
    setColorId(0);
}

const char* TankAlienShip::TANK_ALIEN_SHIP_ART[length] = {
    "[####]",
    "|++++|",
    "\\\\##//"
};

void TankAlienShip::draw(WINDOW* win) const {
    for (int i = 0; i < length; ++i) {
        mvwprintw(win, y + i, x, "%s", TANK_ALIEN_SHIP_ART[i]);
    }
}

void TankAlienShip::shoot() {
    // Implement shooting logic for tank ships
    // Example: Create a bullet object and add it to the game
}

/*
void TankAlienShip::update(double deltaTime) {
    // Decrement the fire rate accumulator every frame
    double newAccumulator = getFireRateAccumulator() - deltaTime;
    setFireRateAccumulator(newAccumulator);
}
*/

 Bullet* TankAlienShip::generateBullet(double deltaTime){
    if(canGenerateBullet(deltaTime)){
        Bullet* newBullet = new Bullet(100, 2.0);  // Damage and speed
        newBullet->setX(this->x + (this->getWidthFromStart() / 2));
        newBullet->setY(this->y + this->getLength());
        newBullet->setDesign('O');
        newBullet->setColorPairId(3);
        newBullet->setType(2);
        return newBullet;
    }
        return nullptr;
    
 }

 std::vector<std::pair<int, int>> TankAlienShip::getShipCoordinates() const {
    std::vector<std::pair<int, int>> coordinates;
    // Iterate over each row of the ship art
    for (int i = 0; i < length; ++i) {
        // Get the current row of the art
        const char* row = TANK_ALIEN_SHIP_ART[i];
        int rowLength = strlen(row);  // Calculate the length of the row
        for (int j = 0; j < rowLength; ++j) {
            if (row[j] != ' ') {  // Consider non-space characters as part of the ship
                coordinates.push_back(std::make_pair(x + j, y + i));
            }
        }
    }
    return coordinates;
}
