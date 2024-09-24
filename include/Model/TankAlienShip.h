// TankAlienShip.h
#ifndef TANK_ALIEN_SHIP_H  // Corrected header guard
#define TANK_ALIEN_SHIP_H

#include "Model/AlienShip.h"
#include "Model/Bullet.h"
#include <ncurses.h>
#include <optional>

#include <vector>
#include <utility> // For std::pair

class TankAlienShip : public AlienShip {
public:
    TankAlienShip(int x, int y);

    
    void draw(WINDOW* win) const override;
    int getWidthFromStart() const override { return widthFromStart; }
    int getLength() const override { return length; }
    std::string getType() const override { return "Tank"; }

    void shoot() override;  // Implement shooting behavior for tank ships
    //void update(double deltaTime);
    Bullet* generateBullet(double deltaTime) override;

    std::vector<std::pair<int, int>> getShipCoordinates() const override;
private:
    static const int length = 3;
    static const int widthFromStart = 5;  // Width from the start position
    static const char* TANK_ALIEN_SHIP_ART[length];
};

#endif // TANK_ALIEN_SHIP_H