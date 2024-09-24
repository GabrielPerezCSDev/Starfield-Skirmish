#ifndef SCREEN_H
#define SCREEN_H

#include "star_queue.h"
class AlienShip;
class PlayerShip;
class Bullet;
#include <ncurses.h>
#include <queue>
#include <memory>

class Screen {
public:
    Screen(int width, int height);
    ~Screen();
    void init();
    // Additional methods as needed
    void updateStars();
    StarQueue& getStarQueue(); // Getter method for starQueue
    WINDOW* getWindow() const;
    void initAlienShips();
    std::vector<std::unique_ptr<AlienShip>>& getAlienShips();  // Getter for alienShips
    void updateAlienShips(double deltaTime);
    int newEnemyX(std::unique_ptr<AlienShip>& ship);
    bool isNextCollision(std::unique_ptr<AlienShip>& ship);
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    bool isNextBorder(std::unique_ptr<AlienShip>& ship);
    void moveAlienShipsDown(double deltaTime); //this will move the alien ships down one level
    double getShipScrollerSpeed(){return shipScrollerSpeed;}
    double getShipScrollerAccum(){return shipScrollerAccum;}
    void setShipScrollerSpeed(double speed){shipScrollerSpeed = speed;}
    void setShipScrollerAccum(double accum){shipScrollerAccum = accum;}

    int hasEnemyReachedBottom();
    const StarQueue& getStarQueue() const { return starQueue; } // Const getter for starQueue
    const std::vector<std::unique_ptr<AlienShip>>& getAlienShips() const { return alienShips; } // Const getter for alienShips

    void setNumTimesScrolled(int num) {numTimesScrolled = num;}
    int getNumTimesScrolled() {return numTimesScrolled;}

    void addNewAlienShips();

    std::unique_ptr<PlayerShip>& getPlayerShip(){return playerShip;};
    void initPlayerShip();

    std::unique_ptr<PlayerShip> const& getPlayerShip() const { return playerShip; }

    void movePlayer(char direc);

    void firePlayerBullet(double deltaTime);
    const std::vector<Bullet>& getPlayerBullets() const {return playerBullets;}
    const std::vector<Bullet>& getPlayerBullets()  {return playerBullets;}
    const std::vector<Bullet>& getEnemyBullets() const {return enemyBullets;}
    const std::vector<Bullet>& getEnemyBullets()  {return enemyBullets;}
    void movePlayerBullets(double deltaTime);
    void moveEnemyBullets(double deltaTime);

    void updateAccumulators(double deltaTime);
    void fireEnemyBullet(double deltaTime);

    void checkForEnemyBulletCollisions();

    int checkShipHealth();
    void checkForPlayerBulletCollisions();
    void removeDestroyedShips();
    void increaseLevel();

    double getLevel(){return level;}
    double getLevel() const {return level;}
    void setLevel(double l){level = l;}
    void updateShips();
    void updateScrollSpeed();
    void updateShipProperties(std::unique_ptr<AlienShip>& ship);
    int calculateNumOfShipsBasedOnLevel();

    
    void clearAndDeleteWindow();  // Method to clear and delete the window
private:
    int width, height;
    WINDOW* win;
    StarQueue starQueue;  // Queue of stars
    std::vector<std::unique_ptr<AlienShip>> alienShips;
    double shipScrollerSpeed;
    double shipScrollerAccum;
    int numTimesScrolled;
    std::unique_ptr<PlayerShip> playerShip;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<AlienShip*> shipsToRemove;
    double level;

};

#endif // SCREEN_H