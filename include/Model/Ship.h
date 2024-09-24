#ifndef SHIP_H
#define SHIP_H

#include <ncurses.h>
#include <string>
#include "Model/screen.h"
class Ship {
public:
    Ship(int x, int y, int hp) : x(x), y(y), hp(hp) {}
    virtual ~Ship() {}

    virtual void update(double deltaTime) = 0;
    virtual void draw(WINDOW* win) const = 0;
    virtual std::string getType() const = 0;

    // Dimension methods now part of the base class
    virtual int getWidthFromStart() const = 0;
    virtual int getLength() const = 0;

    // Common getters and setters
    int getHp() const { return hp; }
    void setHp(int newHp) { hp = newHp; }

    int getX() const { return x; }
    void setX(int newX) { x = newX; }

    int getY() const { return y; }
    void setY(int newY) { y = newY; }

    int getMaxHp() const {return maxHp;}
    void setMaxHp(int hp){maxHp = hp;}
protected:
    int x, y;  // Coordinates of the ship
    int hp;    // Health points of the ship
    int maxHp;
};

#endif // SHIP_H