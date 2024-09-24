#ifndef FAST_ALIEN_SHIP_H
#define FAST_ALIEN_SHIP_H

#include "Model/AlienShip.h"
#include "Model/Bullet.h"
#include <ncurses.h>
#include <optional>

#include <vector>
#include <utility> // For std::pair

class FastAlienShip : public AlienShip {
public:
    // Constructor that initializes the FastAlienShip with specific hp for fast ships
    FastAlienShip(int x, int y);  // Constructor declaration

    
    void draw(WINDOW* win) const override;  // Draw the fast ship on the screen
    int getWidthFromStart() const override { return widthFromStart; }  // Specific width for fast ships
    int getLength() const override { return length; }  // Specific length for fast ships
    std::string getType() const override { return "Fast"; }  // Return the type of ship

    void shoot() override;  // Implement shooting behavior for fast ship
    
    //void update(double deltaTime);
    //Bullet* generateBullet(double deltaTime);
    //bool canGenerateBullet(double deltaTime);

    Bullet* generateBullet(double deltaTime) override;

    std::vector<std::pair<int, int>> getShipCoordinates() const override;

private:
    static const int length = 2;  // Length of the ship
    static const int widthFromStart = 4;  // Width from the start position
    static const char* FAST_ALIEN_SHIP_ART[length];  // Artwork for the fast ship
};

#endif // FAST_ALIEN_SHIP_H