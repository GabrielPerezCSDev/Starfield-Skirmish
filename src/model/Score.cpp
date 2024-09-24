#include "Model/Score.h"

// Define the high score variable
int highScore = 0;

// Function to get the current high score
int getHighScore() {
    return highScore;
}

// Function to update the high score if the new score is higher
bool updateHighScore(int newScore) {
    if (newScore > highScore) {
        highScore = newScore;
        return true;
    }
    return false;
}