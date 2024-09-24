#include "Model/screen.h"
#include "Model/AlienShip.h"
#include "Model/PlayerShip.h"
#include "Model/Score.h"    
#include <iostream> // Include for std::cerr
#include <cstring>
void drawStars(const Screen& screen){
    
    //get the current stars and redraw them on the screen 
    int y = 1; //starting position (draws at top row)
    const StarQueue& sq = screen.getStarQueue(); // Use reference to avoid copying
    for (int i = 0; i < sq.getCapacity(); i++) {
        Star** starArray = sq.getArray(i);
        int x = 1; //initialize the width at zero for new row
        for (int j = 0; j < sq.getStripLength(); j++) {
            if (starArray[j] != nullptr) {
                // Correctly access the symbol of the star
                mvwaddch(screen.getWindow(),y, x, starArray[j]->symbol);
                //std::cerr << "Drawing star at (" << x << ", " << y << ")\n"; // Debug output for each star drawn
            }
            x++; //increment the width to move to the next column for drawing
        }
        y++; //increment the length to move to the next row for drawing
    }
}

void drawShips(const Screen& screen){
    const auto& shipsVector = screen.getAlienShips(); // Get the vector of ships

    // Process each ship in the vector
    for (auto& ship : shipsVector) {
        wattron(screen.getWindow(), COLOR_PAIR(ship->getColorId()));
        ship->draw(screen.getWindow()); // Draw the ship using its draw method
        wattroff(screen.getWindow(), COLOR_PAIR(ship->getColorId()));
    }
}

void drawPlayer(const Screen& screen){
    screen.getPlayerShip()->draw(screen.getWindow());
}

void drawPlayerBullets(const Screen& screen){
    const std::vector<Bullet>& bullets = screen.getPlayerBullets();  // Get the vector of bullets

    for (const Bullet& bullet : bullets) {
        // Turn on color attribute
        wattron(screen.getWindow(), COLOR_PAIR(bullet.getColorPairId()));
        // Get the position and design of each bullet
        int x = bullet.getX();
        int y = bullet.getY();
        char design = bullet.getDesign();

        // Draw the bullet on the screen at its position
        mvwaddch(screen.getWindow(), y, x, design);
        // Turn off color attribute
        wattroff(screen.getWindow(), COLOR_PAIR(bullet.getColorPairId()));
    }

    // Refresh the window to update the screen
    wrefresh(screen.getWindow());

}

void drawEnemyBullets(const Screen& screen){
    const std::vector<Bullet>& bullets = screen.getEnemyBullets();  // Get the vector of bullets

    for (const Bullet& bullet : bullets) {
        // Turn on color attribute
        wattron(screen.getWindow(), COLOR_PAIR(bullet.getColorPairId()));
        // Get the position and design of each bullet
        int x = bullet.getX();
        int y = bullet.getY();
        char design = bullet.getDesign();

        // Draw the bullet on the screen at its position
        mvwaddch(screen.getWindow(), y, x, design);
        // Turn off color attribute
        wattroff(screen.getWindow(), COLOR_PAIR(bullet.getColorPairId()));
    }

    // Refresh the window to update the screen
    wrefresh(screen.getWindow());

}

//draw all after update 
void drawAll(const Screen& screen){
    // Clear the window before drawing the new frame
    werase(screen.getWindow());
    // Redraw the border
    box(screen.getWindow(), 0, 0);
    drawStars(screen);
    drawShips(screen);
    drawPlayer(screen);
    drawPlayerBullets(screen);
    drawEnemyBullets(screen);
    // Refresh the window to display the updated content
    wrefresh(screen.getWindow());

    //soon to be added methods for the following 
    //bullets
    
}

void overlayEndingOne(const Screen& screen, bool isHighScore) {
    clear();  // Clear the screen
    drawAll(screen);  // Redraw the screen with its current state

    int maxY = screen.getHeight();
    int maxX = screen.getWidth();

    const char* gameOverMessage = "Game Over: Enemy has reached the bottom!";
     const char* quitMessage = "Press Escape to return to main menu";

    // Calculate message positions
    int gameOverMessageLength = strlen(gameOverMessage);
    int quitMessageLength = strlen(quitMessage);

    int posY = maxY / 2 - 1;  // Start one line above the center for the first message
    int posXGameOver = (maxX - gameOverMessageLength) / 2;  // Center the game over message horizontally
    int posXQuit = (maxX - quitMessageLength) / 2;  // Center the quit message horizontally

    // Print messages
    mvprintw(posY, posXGameOver, "%s", gameOverMessage);
    mvprintw(posY + 1, posXQuit, "%s", quitMessage);  // Print below the restart message

    if(isHighScore){
        const char* highScoreMessage = "!NEW HIGH SCORE!";
        int highScoreMessageLength = strlen(highScoreMessage);
        int posXHighScore = (maxX - highScoreMessageLength) / 2;  // Center the high score message horizontally
        mvprintw(posY + 3, posXHighScore, "%s", highScoreMessage);  // Print below the quit message

        // Display the new high score value
        const char* highScoreValueMessage = "Score: %d";
        char highScoreValueBuffer[50]; // Buffer to hold the formatted high score message
        sprintf(highScoreValueBuffer, highScoreValueMessage, getHighScore()); // Format the high score message
        int highScoreValueLength = strlen(highScoreValueBuffer);
        int posXHighScoreValue = (maxX - highScoreValueLength) / 2;  // Center the high score value message horizontally
        mvprintw(posY + 4, posXHighScoreValue, "%s", highScoreValueBuffer);  // Print below the high score message
    }

    refresh();  // Refresh the screen to show the messages
}

void overlayEndingTwo(const Screen& screen, bool isHighScore) {
    clear();  // Clear the screen
    drawAll(screen);  // Redraw the screen with its current state

    int maxY = screen.getHeight();
    int maxX = screen.getWidth();

    const char* gameOverMessage = "Game Over: An enemy has collided with you!";
    const char* quitMessage = "Press Escape to return to main menu";

    // Calculate message positions
    int gameOverMessageLength = strlen(gameOverMessage);
    int quitMessageLength = strlen(quitMessage);

    int posY = maxY / 2 - 1;  // Start one line above the center for the first message
    int posXGameOver = (maxX - gameOverMessageLength) / 2;  // Center the game over message horizontally
    int posXQuit = (maxX - quitMessageLength) / 2;  // Center the quit message horizontally

    // Print messages
    mvprintw(posY, posXGameOver, "%s", gameOverMessage);
    mvprintw(posY + 1, posXQuit, "%s", quitMessage);  // Print below the restart message

    if(isHighScore){
        const char* highScoreMessage = "!NEW HIGH SCORE!";
        int highScoreMessageLength = strlen(highScoreMessage);
        int posXHighScore = (maxX - highScoreMessageLength) / 2;  // Center the high score message horizontally
        mvprintw(posY + 3, posXHighScore, "%s", highScoreMessage);  // Print below the quit message

        // Display the new high score value
        const char* highScoreValueMessage = "Score: %d";
        char highScoreValueBuffer[50]; // Buffer to hold the formatted high score message
        sprintf(highScoreValueBuffer, highScoreValueMessage, getHighScore()); // Format the high score message
        int highScoreValueLength = strlen(highScoreValueBuffer);
        int posXHighScoreValue = (maxX - highScoreValueLength) / 2;  // Center the high score value message horizontally
        mvprintw(posY + 4, posXHighScoreValue, "%s", highScoreValueBuffer);  // Print below the high score message
    }

    refresh();  // Refresh the screen to show the messages
}

void overlayEndingThree(const Screen& screen, bool isHighScore) {
    clear();  // Clear the screen
    drawAll(screen);  // Redraw the screen with its current state

    int maxY = screen.getHeight();
    int maxX = screen.getWidth();

    const char* gameOverMessage = "Game Over: You have lost all of your health!";
    const char* quitMessage = "Press Escape to return to main menu";

    // Calculate message positions
    int gameOverMessageLength = strlen(gameOverMessage);
    int quitMessageLength = strlen(quitMessage);

    int posY = maxY / 2 - 1;  // Start one line above the center for the first message
    int posXGameOver = (maxX - gameOverMessageLength) / 2;  // Center the game over message horizontally
    int posXQuit = (maxX - quitMessageLength) / 2;  // Center the quit message horizontally

    // Print messages
    mvprintw(posY, posXGameOver, "%s", gameOverMessage);
    mvprintw(posY + 1, posXQuit, "%s", quitMessage);  // Print below the restart message


    if(isHighScore){
        const char* highScoreMessage = "!NEW HIGH SCORE!";
        int highScoreMessageLength = strlen(highScoreMessage);
        int posXHighScore = (maxX - highScoreMessageLength) / 2;  // Center the high score message horizontally
        mvprintw(posY + 3, posXHighScore, "%s", highScoreMessage);  // Print below the quit message

        // Display the new high score value
        const char* highScoreValueMessage = "Score: %d";
        char highScoreValueBuffer[50]; // Buffer to hold the formatted high score message
        sprintf(highScoreValueBuffer, highScoreValueMessage, getHighScore()); // Format the high score message
        int highScoreValueLength = strlen(highScoreValueBuffer);
        int posXHighScoreValue = (maxX - highScoreValueLength) / 2;  // Center the high score value message horizontally
        mvprintw(posY + 4, posXHighScoreValue, "%s", highScoreValueBuffer);  // Print below the high score message
    }

    refresh();  // Refresh the screen to show the messages
}

void printGameInfo(const Screen& screen) {
    int infoPosX = screen.getWidth() + 2; // Position the info to the right of the game screen
    int posY = 1; // Start from the top

    // Prepare a message about the number of alien ships
    char shipInfoMsg[50]; // Ensure this buffer is large enough
    if (!screen.getAlienShips().empty()) {
        snprintf(shipInfoMsg, sizeof(shipInfoMsg), "Alien Ships: %ld              ", screen.getAlienShips().size());
    } else {
        snprintf(shipInfoMsg, sizeof(shipInfoMsg), "No ships currently.          "); // Padding to clear previous text
    }
    mvprintw(posY++, infoPosX, "%s", shipInfoMsg);

    // Print player ship info
    const auto& playerShip = screen.getPlayerShip();
    mvprintw(posY++, infoPosX, "Fire Rate (bullets/s): %.2f", screen.getPlayerShip()->getFireRate());
    mvprintw(posY++, infoPosX, "Accumulator (when <= 0 can fire): %.2f", playerShip->getFireRateAccumulator());
    mvprintw(posY++, infoPosX, "Player Bullets (Active): %ld", screen.getPlayerBullets().size());
    mvprintw(posY++, infoPosX, "Enemy Bullets (Active): %ld", screen.getEnemyBullets().size());
    mvprintw(screen.getHeight()-4, infoPosX, "Level: %d", static_cast<int>(screen.getLevel()));
    mvprintw(screen.getHeight()-3, infoPosX, "Player HP: %d", playerShip->getHp());
    mvprintw(screen.getHeight()-2, infoPosX, "Player Score: %d", playerShip->getScore());

    refresh(); // Refresh the screen to show the updates
}