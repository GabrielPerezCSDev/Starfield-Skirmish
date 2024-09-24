#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "Model/Ship.h"
#include "Model/Bullet.h"
#include <ncurses.h>
#include <optional>

#include <vector>
#include <utility> // For std::pair

class PlayerShip : public Ship {
public:
    virtual ~PlayerShip() {}
    PlayerShip(int x, int y);

    void update(double deltaTime) override;  // To be implemented based on player input
    void draw(WINDOW* win) const override;
    std::string getType() const override { return "Player"; }
    void shoot();  // Specific shooting behavior for the player ship

    int getWidthFromStart() const override { return widthFromStart; }
    int getLength() const override { return length; }
    // Getter and setter for score
    int getScore() const { return score; }
    void setScore(int newScore) { score = newScore; }

    // Method to get an array of coordinates covering the player ship
    std::vector<std::pair<int, int>> getPlayerCoordinates() const;

   Bullet* generateBullet(double deltaTime);
    bool canGenerateBullet(double deltaTime);

    void setFireRate(double fire){fireRate = fire;}
    double getFireRate(){return fireRate;}
    void setFireRateAccumulator(double fire){fireRateAccumulator = fire;}
    double getFireRateAccumulator(){return fireRateAccumulator;}
    //void update(double deltaTime);

private:
    static const int widthFromStart = 4;  // Example width
    static const int length = 1;  // Example length
    static const char* PLAYER_SHIP_ART[length];  // Artwork for the player ship
    int score;  // Score attribute for the player ship
    double fireRate;
    double fireRateAccumulator;
};


#endif // PLAYER_SHIP_H