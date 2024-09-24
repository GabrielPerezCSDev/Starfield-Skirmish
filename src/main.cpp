#include "Model/screen.h"
#include "View/game_view.h"
#include "Model/Score.h"
#include "Model/PlayerShip.h"
#include "View/main_menu_view.h"
#include "View/info_view.h"
// Include other necessary headers
#include <ncurses.h>
#include <chrono>
#include <thread>

bool endScreenOne(const Screen& screen) {
    // Update the high score with the score from the current game session
    bool isHighScore = updateHighScore(screen.getPlayerShip()->getScore());
    overlayEndingOne(screen, isHighScore);  // Show the game over message

    int ch;
    nodelay(stdscr, FALSE);  // Disable non-blocking mode to wait for input
    while (true) {
        ch = getch();
        if (ch == 27) {  // Escape key pressed
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            return false;  // return to main menu
        }
    }
}

bool endScreenTwo(const Screen& screen) {
    // Update the high score with the score from the current game session
    bool isHighScore = updateHighScore(screen.getPlayerShip()->getScore());
    overlayEndingTwo(screen, isHighScore);  // Show the game over message

    int ch;
    nodelay(stdscr, FALSE);  // Disable non-blocking mode to wait for input
    while (true) {
        ch = getch();
        
        if (ch == 27) {  // Escape key pressed
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            return false;  // return to main menu
        }
    }
}

bool endScreenThree(const Screen& screen) {
    // Update the high score with the score from the current game session
    bool isHighScore = updateHighScore(screen.getPlayerShip()->getScore());
    overlayEndingThree(screen, isHighScore);  // Show the game over message

    int ch;
    nodelay(stdscr, FALSE);  // Disable non-blocking mode to wait for input
    while (true) {
        ch = getch();
        
        if (ch == 27) {  // Escape key pressed
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            return false;  // return to main menu
        }
    }
}

// Function to run the main game loop
bool runGameLoop() {
    Screen screen(100, 30); // Set screen size to 100x30
    screen.init();

    const int TARGET_FPS = 60;
    const std::chrono::milliseconds TARGET_FRAME_DURATION(1000 / TARGET_FPS);
    
    const int STAR_UPDATE_FPS = 1; // Target updates per second for stars
    const std::chrono::milliseconds STAR_UPDATE_DURATION(1000 / STAR_UPDATE_FPS);
    auto lastStarUpdateTime = std::chrono::steady_clock::now();
    auto lastUpdateTime = std::chrono::steady_clock::now();

    int ch;
    int endGame = 0;
    while (true) {
        auto frameStart = std::chrono::steady_clock::now();

        ch = wgetch(screen.getWindow()); // Read a character from the keyboard, non-blocking
        auto currentTime = std::chrono::steady_clock::now();
        double deltaTime = std::chrono::duration<double, std::chrono::seconds::period>(currentTime - lastUpdateTime).count();
        if (ch == 27) {  // Escape key pressed
            screen.clearAndDeleteWindow();
             clear();  // Clear the screen
            refresh();  // Apply the clearing
            return true;  // Exit the loop and do not restart
        }
        // Handle left and right arrow keys
        if (ch == KEY_LEFT) {
            screen.movePlayer('w');  // You need to implement this method in Screen or Player class
        } else if (ch == KEY_RIGHT) {
            screen.movePlayer('e');  // You need to implement this method in Screen or Player class
        }else if(ch == ' ' || ch == 32){
            screen.firePlayerBullet(deltaTime);
        }
        
        
        lastUpdateTime = currentTime;

        if (currentTime - lastStarUpdateTime >= STAR_UPDATE_DURATION) {
            screen.updateStars(); // Update the stars in the background
            lastStarUpdateTime = currentTime;
        }
        screen.fireEnemyBullet(deltaTime);
        screen.updateAlienShips(deltaTime);
        screen.moveAlienShipsDown(deltaTime);
        screen.movePlayerBullets(deltaTime);
        screen.updateAccumulators(deltaTime);
        screen.moveEnemyBullets(deltaTime);
        screen.checkForEnemyBulletCollisions();
        screen.checkForPlayerBulletCollisions();

        endGame = screen.hasEnemyReachedBottom();
        if (endGame == 1) { //enemy readhed bottom
            screen.clearAndDeleteWindow();
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            bool restart = endScreenOne(screen);
            if (!restart) {
                return true;  // Return to main menu if not restarting
            }
        }
        if(endGame == 2){ //enemy hit the player 
            screen.clearAndDeleteWindow();
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            bool restart = endScreenTwo(screen);
            if (!restart) {
                return true;  // Return to main menu if not restarting
            }
        }

        //check the next condition for ending the gamw iff it passes
        endGame = screen.checkShipHealth();
        if(endGame == 3){
            screen.clearAndDeleteWindow();
            clear();  // Clear the screen
            refresh();  // Apply the clearing
            bool restart = endScreenThree(screen);
            if (!restart) {
                return true;  // Return to main menu if not restarting
            }
        }

        drawAll(screen);
        printGameInfo(screen);

        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration = frameEnd - frameStart;
        auto sleepDuration = TARGET_FRAME_DURATION - frameDuration;

        if (sleepDuration > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}


// Main function
int main() {
    srand(time(0));  // Initialize random seed at the start of the program
    MainMenuView mainMenu;
    InfoView infoView;
    bool gameRunning = true;

    while (gameRunning) {
        clear(); // Clear the entire screen
        refresh(); // Apply the clearing
        int selection = mainMenu.showMenu();

        switch (selection) {
            case 0: // Start Game
                gameRunning = runGameLoop();
                break;
            case 1: // Info
                infoView.showInfo();
                break;
            case 2: // Quit Game
                gameRunning = false; // Exit the program
                break;
        }
    }

    return 0;
}

