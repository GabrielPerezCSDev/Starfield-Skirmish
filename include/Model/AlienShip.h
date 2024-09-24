// AlienShip.h
#ifndef ALIEN_SHIP_H
#define ALIEN_SHIP_H

#include "Model/screen.h"
#include "Model/Ship.h"  // Ensure this path is correct
#include <memory>

class AlienShip : public Ship {
public:
    // Utilize the constructor of the base Ship class
    AlienShip(int x, int y, int hp) : Ship(x, y, hp) {}

    // Destructor
    virtual ~AlienShip() {}

    // Override the update method from Ship
    void update(double deltaTime) override;

    // Pure virtual function for shooting functionality
    virtual void shoot() = 0;

    // The getters and setters for hp, speed, x, y, and direction are now inherited from Ship
    // No need to redeclare them here unless you're adding additional logic specific to AlienShips

    // Pure virtual functions for ship type, dimensions, and drawing, which must be implemented by derived classes
    virtual std::string getType() const override = 0;
    virtual void draw(WINDOW* win) const override = 0;

    // Specific functionality for AlienShip
    void flipDirection()  {
        direc = (direc == 'e') ? 'w' : 'e';  // Flip direction
    }

    // Getter and setter for direc
    char getDirec() const { return direc; }
    void setDirec(char newDirec) { direc = newDirec; }
    static std::unique_ptr<AlienShip> createShip(const std::string& type, int x, int y);
    double getSpeed() const { return speed; }
    void setSpeed(double newSpeed) { speed = newSpeed; }

    void setFireRate(double fire){fireRate = fire;}
    double getFireRate(){return fireRate;}
    void setFireRateAccumulator(double fire){fireRateAccumulator = fire;}
    double getFireRateAccumulator(){return fireRateAccumulator;}
    void updateAcum(double deltaTime);
     bool canGenerateBullet(double deltaTime);\
     virtual Bullet* generateBullet(double deltaTime) = 0;

     // Method to get an array of coordinates covering the player ship
    virtual std::vector<std::pair<int, int>> getShipCoordinates() const = 0;

    int getColorId(){return colorId;}
    void setColorId(double id){colorId = id;}

protected:
    char direc;  // Direction of the ship, specific to AlienShip for AI behavio
    double moveAccumulator;  // Time accumulator for movement
    double speed;
    double fireRate;
    double fireRateAccumulator;
    int colorId;
};


#endif // ALIEN_SHIP_H