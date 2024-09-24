#ifndef SCORE_H
#define SCORE_H

// Declare high score variable as extern
extern int highScore;

// Function to get the current high score
int getHighScore();

// Function to update the high score if the new score is higher
bool updateHighScore(int newScore);

#endif // SCORE_H