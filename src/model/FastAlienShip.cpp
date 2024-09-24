#include "Model/FastAlienShip.h"
#include <cstring> // Include for strlen

const char* FastAlienShip::FAST_ALIEN_SHIP_ART[length] = {
    "  |> ",
    "/|||\\"
};

FastAlienShip::FastAlienShip(int x, int y) : AlienShip(x, y, 50) {  // Pass only x, y, and hp to the base constructor
    speed = 10.0;  // Set the specific speed for FastAlienShip
    setFireRateAccumulator(0.0);
    setFireRate(0.5);
    setMaxHp(50);
    setColorId(0);
}

void FastAlienShip::draw(WINDOW* win) const {
    for (int i = 0; i < length; ++i) {
        mvwprintw(win, y + i, x, "%s", FAST_ALIEN_SHIP_ART[i]);
    }
}

void FastAlienShip::shoot() {
    //shoot basically means it will add the shot to the enemyBullets queue 
}
/*
void FastAlienShip::update(double deltaTime) {
    
}
*/

Bullet* FastAlienShip::generateBullet(double deltaTime) {
    if(canGenerateBullet(deltaTime)){
        int damage = 50;
        int speed = 4.0;
        Bullet* newBullet = new Bullet(damage, speed);  // Damage and speed
        newBullet->setX(this->x + (this->getWidthFromStart() / 2));
        newBullet->setY(this->y + this->getLength());
        newBullet->setDesign('|');
        newBullet->setColorPairId(2);
        newBullet->setType(2);
        return newBullet;
    }
        return nullptr;
    
}

 std::vector<std::pair<int, int>> FastAlienShip::getShipCoordinates() const {
    std::vector<std::pair<int, int>> coordinates;
    // Iterate over each row of the ship art
    for (int i = 0; i < length; ++i) {
        // Get the current row of the art
        const char* row = FAST_ALIEN_SHIP_ART[i];
        int rowLength = strlen(row);  // Calculate the length of the row
        for (int j = 0; j < rowLength; ++j) {
            if (row[j] != ' ') {  // Consider non-space characters as part of the ship
                coordinates.push_back(std::make_pair(x + j, y + i));
            }
        }
    }
    return coordinates;
}