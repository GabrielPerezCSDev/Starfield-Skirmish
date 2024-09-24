#include "Model/screen.h"
#include "View/game_view.h"
#include "Model/FastAlienShip.h" // Assuming this is the correct header file for FastAlienShip
#include "Model/TankAlienShip.h"
#include "Model/PlayerShip.h"
#include "Model/Utility.h"
#include "Model/Bullet.h"
#include <cstdlib> // For rand()
#include <ctime> // For time()
#include <algorithm>

Screen::Screen(int width, int height) : width(width), height(height), win(nullptr), starQueue(width-2, height-1), shipScrollerSpeed(0.5) {
    setNumTimesScrolled(0);
    setLevel(1.0); //level one for start
    // Constructor now initializes starQueue with dimensions
    starQueue.init_queue(); //set the stars queue
    initAlienShips();
    //now create a player ship 
    initPlayerShip();
}

Screen::~Screen() {
    endwin();
}

void Screen::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    win = newwin(height, width, 0, 0);
    keypad(win, TRUE);
    nodelay(win, TRUE);
    box(win, 0 , 0);
    wrefresh(win);
    start_color(); // Initialize color functionality
    init_pair(0, COLOR_WHITE, COLOR_BLACK); //define a default white color
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // color of player bullets (never changes)
    init_pair(2, COLOR_RED, COLOR_BLACK); // color of fast ships bullets (never chnages)
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // color of tank bullets (never chnages)
    init_pair(4, COLOR_BLUE, COLOR_BLACK); //blue for level two ships 
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // Magenta for level three ships
    init_pair(6, COLOR_CYAN, COLOR_BLACK); // Cyan for level four ships
    init_pair(7, COLOR_WHITE, COLOR_BLUE); // Example: White text on blue background for level five ships
    init_pair(8, COLOR_BLACK, COLOR_GREEN); // Example: Black text on green background for level six ships
    //now need to call the view to display the stars and stuff on the screen 
    drawAll(*this);

}

// Implement additional methods
void Screen::updateStars() {
    starQueue.dequeue();
    starQueue.enqueue(); 
}

// Implementation of the getter method
StarQueue& Screen::getStarQueue() {
    return starQueue;
}

WINDOW* Screen::getWindow() const {
    return win;  // Return the window pointer
}

void Screen::initAlienShips(){
    
    //srand(time(0)); // Ideally, move this to the main function or similar initialization section

    int numOfShips = calculateNumOfShipsBasedOnLevel();
    //int numOfShips = 6;
    char directions[] = {'e', 'w'};
    std::string shipTypes[] = {"Fast", "Tank"};

    for (int i = 0; i < numOfShips; ++i) {
        std::string chosenType = shipTypes[rand() % 2];
        auto ship = AlienShip::createShip(chosenType, 0, 1);

        bool positionValid;
        int attempts = 0;
        do {
            positionValid = true;
            int shipX = rand() % (width - 2 * ship->getWidthFromStart()) + ship->getWidthFromStart();
            ship->setX(shipX);
            ship->setDirec(directions[rand() % 2]);

            // Check for overlap with existing ships
            for (auto& existingShip : alienShips) {
                int existingLeft = existingShip->getX();
                int existingRight = existingLeft + existingShip->getWidthFromStart() * 2;

                int newLeft = ship->getX();
                int newRight = newLeft + ship->getWidthFromStart() * 2;

                if (newLeft <= existingRight && newRight >= existingLeft) {
                    positionValid = false;
                    break;
                }
            }
            attempts++;
            if (attempts > 50) { // Prevent infinite loops
                positionValid = true; // Accept overlap if no valid position found after many attempts
            }
        } while (!positionValid);

        alienShips.push_back(std::move(ship));
    }

}

std::vector<std::unique_ptr<AlienShip>>& Screen::getAlienShips() {
    return alienShips;
}


void Screen::updateAlienShips(double deltaTime){
    for (auto& ship : alienShips) {
        bool isBorder = isNextBorder(ship);
        bool isCollision = isNextCollision(ship);
        if (isBorder || isCollision) {
            ship->flipDirection();
            //skip this ships turn so it does not move for now 
            return;
        }
        //make sure it does not update if it is going to go out of bounds 

        ship->update(deltaTime);
    }
}


int Screen::newEnemyX(std::unique_ptr<AlienShip>& ship){
    //check if it is going to hit right or left border and update the direction to flip 
    int x = ship->getX();
    char dir =  ship->getDirec(); 
    //shift ship over 1
    int newX = (dir == 'e') ? x + 1 : x -1;

    return newX;
}

bool Screen::isNextCollision(std::unique_ptr<AlienShip>& ship){
    int newX = newEnemyX(ship);
    int leftX = newX;
    int rightX = newX + ship->getWidthFromStart(); //the width is the characters of the ship from the left

    for (auto& checkShip : alienShips) {
        if (checkShip.get() == ship.get()) continue; // Skip checking against itself
        if (checkShip->getY() != ship->getY()) continue; //skip checking if not on the same level
        int checkLeftX = checkShip->getX();
        int checkRightX = checkShip->getX() + checkShip->getWidthFromStart();

        // Check for overlap
        if (leftX <= checkRightX && rightX >= checkLeftX) {
            return true; // Collision detected
        }
    }
    return false; // No collision
    }

bool Screen::isNextBorder(std::unique_ptr<AlienShip>& ship){
        int newX = newEnemyX(ship);
        return (newX == getWidth() - ship->getWidthFromStart() - 1 || newX == 0);  // Assuming 0 is the left border
}


void Screen::moveAlienShipsDown(double deltaTime){
    
    // Update the accumulator by subtracting deltaTime
    double newAccumulator = getShipScrollerAccum() - deltaTime;
    setShipScrollerAccum(newAccumulator);

    // Check if it's time to move ships down
    if (getShipScrollerAccum() <= 0) {
        // Increment the counter for the number of moves
        setNumTimesScrolled(getNumTimesScrolled() + 1);

        // Move each ship down by one unit
        for (auto& ship : alienShips) {
            int newY = ship->getY() + 1;
            ship->setY(newY);
        }

        // Reset the accumulator based on the ship scroller speed
        setShipScrollerAccum(1.0 / getShipScrollerSpeed());

        // Check if it's time to add a new line of ships
        if (getNumTimesScrolled() % 8 == 0) {
            addNewAlienShips();
        }

        //check fo increasing level 
        if(getNumTimesScrolled() % 24 == 0){
            increaseLevel();
        }
    }
}

int Screen::hasEnemyReachedBottom(){

    //go through each unit and see if they are at the bottom 
    for (auto& ship : alienShips) {
            if(ship->getY() + ship->getLength()  == getHeight()){
                return 1;
            } 
        
            // Check for collision with the player ship
        for (const auto& coord : getPlayerShip()->getPlayerCoordinates()) {
            int shipLeftX = ship->getX();
            int shipRightX = shipLeftX + ship->getWidthFromStart();
            int shipY = ship->getY();

            // Check if the alien ship's Y coordinate matches the player's Y coordinate
            // and if the X coordinates overlap with any player coordinate
            if (shipY == coord.second && shipLeftX <= coord.first && shipRightX >= coord.first) {
                return 2; // Collision detected
            }
        }
        }
    return 0;
}

int Screen::calculateNumOfShipsBasedOnLevel() {
    int level = static_cast<int>(getLevel());
    int minShips, maxShips;

    // Determine the range of ships based on the current level
    switch(level) {
        case 1:
            minShips = 1; maxShips = 2;
            break;
        case 2:
            minShips = 1; maxShips = 3;
            break;
        case 3:
            minShips = 2; maxShips = 4;
            break;
        case 4:
            minShips = 2; maxShips = 5;
            break;
        case 5:
            minShips = 3; maxShips = 6;
            break;
        case 6:
            minShips = 3; maxShips = 7;
            break;
        default: // For level >= 7
            minShips = 4; maxShips = 7;
            break;
    }

    // Return a random number of ships within the determined range
    return rand() % (maxShips - minShips + 1) + minShips;
}

void Screen::addNewAlienShips(){
    
    //srand(time(0));  // Ideally, move this to the main function or similar initialization section

    int numOfShips = calculateNumOfShipsBasedOnLevel();
    //int numOfShips =1;
    char directions[] = {'e', 'w'};
    std::string shipTypes[] = {"Fast", "Tank"};
    std::vector<std::unique_ptr<AlienShip>> newShips;  // Temporary vector for new ships

    for (int i = 0; i < numOfShips; ++i) {
        std::string chosenType = shipTypes[rand() % 2];
        auto ship = AlienShip::createShip(chosenType, 0, 1);

        bool positionValid;
        int attempts = 0;
        do {
            positionValid = true;
            int shipX = rand() % (width - 2 * ship->getWidthFromStart()) + ship->getWidthFromStart();
            ship->setX(shipX);
            ship->setDirec(directions[rand() % 2]);

            // Check for overlap with other new ships
            for (auto& existingShip : newShips) {
                int existingLeft = existingShip->getX();
                int existingRight = existingLeft + existingShip->getWidthFromStart() * 2;

                int newLeft = ship->getX();
                int newRight = newLeft + ship->getWidthFromStart() * 2;

                if (newLeft <= existingRight && newRight >= existingLeft) {
                    positionValid = false;
                    break;
                }
            }
            attempts++;
            if (attempts > 50) { // Prevent infinite loops
                positionValid = true; // Accept overlap if no valid position found after many attempts
            }
        } while (!positionValid);
        updateShipProperties(ship); //update the ships based on level
        newShips.push_back(std::move(ship));  // Add the new ship to the temporary vector
    }

    // Merge new ships into the main alienShips vector
    for (auto& ship : newShips) {
        alienShips.push_back(std::move(ship));
    }

}

void Screen::updateShipProperties(std::unique_ptr<AlienShip>& ship) {
    // Set the color based on level
    switch(static_cast<int>(getLevel())) {
        case 1:
            // Do nothing
            break;
        case 2:
            ship->setColorId(4); // level 2 has blue ships
            break;
        case 3:
            ship->setColorId(5); // level 3 has magenta
            break;
        case 4:
            ship->setColorId(6); // level 4 has cyan
            break;
        case 5:
            ship->setColorId(7); // level 5 is white and blue
            break;
        default:
            ship->setColorId(8); // level 6 and above black on green
            break; // Nothing happens if it is below here
    }

    // Adjust fire rate and speed based on level
    double speedMod = getLevel() - 1.0; // Basic implementation for now
    double fireRateMod = (getLevel() - 1.0) / 10.0;

    ship->setSpeed(ship->getSpeed() + speedMod);
    ship->setFireRate(ship->getFireRate() + fireRateMod);
}

void Screen::initPlayerShip(){
    //create a new player ship in the middle of the screen for now to test
    // Calculate the middle position of the screen horizontally
    int middleX = width / 2;
    // Decide on the vertical position of the player ship
    // For example, placing it towards the bottom of the screen
    int playerY = height-2; // Adjust this value as needed

    // Create a new PlayerShip with 500 health points (or any other value you deem appropriate)
    playerShip = std::make_unique<PlayerShip>(middleX, playerY);
}

void Screen::movePlayer(char direc){
    //check if it is going to hit right or left border and update the direction to flip 
    int x = getPlayerShip()->getX();
    //shift ship over 1
    int newX = (direc == 'e') ? x + 1 : x -1;

    //check if it is in bounds 
    if(newX < getWidth() - getPlayerShip()->getLength() -4 && newX > 0){
        //set the new x value for the ship 
        getPlayerShip()->setX(newX);
    }
}

void Screen::firePlayerBullet(double deltaTime){
    //get the bullet from player 
     auto bulletOpt = getPlayerShip()->generateBullet(deltaTime);
    //add it to the player bullet vector in screen 
    if(bulletOpt){
        playerBullets.push_back(std::move(*bulletOpt));
    }
    
}

//move the player bullets
void Screen::movePlayerBullets(double deltaTime){
    if(playerBullets.empty()){return;}
    for (auto& bullet : playerBullets) {
        bullet.update(deltaTime);
    }
}
//decide which enemies can fire 


//fiure an enemy bullet 
void Screen::fireEnemyBullet(double deltaTime){
    //iterate through all ships
    for (auto& ship : alienShips) {
        //get the bullet from ship if it can shoot 
        auto bulletOpt = ship->generateBullet(deltaTime);
        //add it to the player bullet vector in screen 
        if(bulletOpt){
            //check if type is a tank ship 
            if(ship->getType() == "Tank"){
                // Copy the bullet and make the new one have its x be one to the right
                std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>(*bulletOpt);
                newBullet->setX(newBullet->getX() + 1); // Adjust the x position of the new bullet

                // Put both bullets in the enemyBullets vector
                enemyBullets.push_back(std::move(*bulletOpt));
                enemyBullets.push_back(std::move(*newBullet));
            }else{
                enemyBullets.push_back(std::move(*bulletOpt));
            }
        }
    }
    
}

void Screen::checkForEnemyBulletCollisions() {
    auto it = enemyBullets.begin();
    while (it != enemyBullets.end()) {
        if(it->getY() >= height){
            it = enemyBullets.erase(it);
        }else{

        bool bulletRemoved = false;
        int bulletX = it->getX();
        int bulletY = it->getY()+1;

        // Get player coordinates
        const auto& playerCoords = getPlayerShip()->getPlayerCoordinates();

        // Manually check each player coordinate for collision
        for (const auto& coord : playerCoords) {
            if (coord.first == bulletX && coord.second == bulletY) {
                // Collision detected with player
                getPlayerShip()->setHp(getPlayerShip()->getHp() - it->getDamage());  // Reduce player HP by bullet damage
                it = enemyBullets.erase(it);  // Remove the bullet
                bulletRemoved = true;
                break;  // Exit the loop since the bullet is removed
            }
        }

        // Check if the bullet has collided with other game elements if not already removed
        if (!bulletRemoved) {
            
            char charAtPosition = mvwinch(getWindow(), bulletY, bulletX) & A_CHARTEXT;  // Get the character at the bullet's position
            if (charAtPosition != '*' && charAtPosition != ' ') {
                // Collision with an object other than empty space or stars
                it = enemyBullets.erase(it);  // Remove the bullet
            } else {
                ++it;  // No collision, move to the next bullet
            }
            
            
        }
        }
    }

}

bool collisionDetected(const Bullet& bullet, const AlienShip& ship) {
    auto shipCoords = ship.getShipCoordinates();
    for (const auto& coord : shipCoords) {
        if (coord.first == bullet.getX() && coord.second == bullet.getY()) {
            return true;
        }
    }
    return false;
}

void Screen::checkForPlayerBulletCollisions() {
     auto bulletIt = playerBullets.begin();
    while (bulletIt != playerBullets.end()) {
        if(bulletIt->getY() <= 0){
            // Bullet is above the screen, remove it
            bulletIt = playerBullets.erase(bulletIt);  
        }else{
            bool bulletRemoved = false;
            for (auto& ship : alienShips) {
                if (collisionDetected(*bulletIt, *ship)) {
                    ship->setHp(ship->getHp() - bulletIt->getDamage());
                    if (ship->getHp() <= 0) {
                        shipsToRemove.push_back(ship.get());  // Mark the ship for removal
                        //increase player score
                        getPlayerShip()->setScore(getPlayerShip()->getScore() + ship->getMaxHp());
                    }
                    bulletIt = playerBullets.erase(bulletIt);  // Remove the bullet
                    bulletRemoved = true;
                    break;  // Stop checking other ships since the bullet is removed
                }
            }
            if (!bulletRemoved) {
                ++bulletIt;  // Move to the next bullet if it wasn't removed
            }
        }
    }
    removeDestroyedShips();
}

void Screen::removeDestroyedShips() {
    auto it = std::remove_if(alienShips.begin(), alienShips.end(),
                             [this](const std::unique_ptr<AlienShip>& ship) {
                                 return std::find(shipsToRemove.begin(), shipsToRemove.end(), ship.get()) != shipsToRemove.end();
                             });
    alienShips.erase(it, alienShips.end());  // Remove the destroyed ships
    shipsToRemove.clear();  // Clear the list after removal
}


void Screen::updateAccumulators(double deltaTime){
    //update the accumulator for the player shots
    getPlayerShip()->update(deltaTime);
    // Update all enemy ships
    for (auto& ship : alienShips) {
        if (ship) {  // Check if the pointer is not null
            ship->updateAcum(deltaTime);
        }
    }
}

//move the enemy bullets
void Screen::moveEnemyBullets(double deltaTime){
    if(enemyBullets.empty()){return;}
    for (auto& bullet : enemyBullets) {
        bullet.update(deltaTime);
    }
}

//check ship health 
int Screen::checkShipHealth(){
    if(getPlayerShip()->getHp() <= 0){
        return 3;
    }
    else{
        return 0;
    }
}

void Screen::updateShips(){
    double speedMod = getLevel() - 1.0; //basic implemntation for now
    double fireRateMod = (getLevel() - 1.0 )/10.0;
    
    for(auto& ship : alienShips){
        ship->setSpeed(ship->getSpeed() + speedMod);
        ship->setFireRate(ship->getFireRate() + fireRateMod);
    }
}

void Screen::updateScrollSpeed(){
    double scrollMod = (getLevel() - 1.0)/6; //increase the rate of scrolling in the game
    setShipScrollerSpeed(getShipScrollerSpeed() + scrollMod);
}

void Screen::increaseLevel(){
    setLevel(getLevel()+1.0); //increase the level by one for now 
    //update speed of ships 
    //updateShips();
    updateScrollSpeed();
}

void Screen::clearAndDeleteWindow() {
    werase(win);  // Clear the window
    wrefresh(win);  // Refresh the window to show the cleared state
    delwin(win);  // Delete the window to free resources
    win = nullptr;  // Set the window pointer to nullptr to avoid dangling references
}