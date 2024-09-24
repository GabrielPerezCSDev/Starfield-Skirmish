#include "View/info_view.h"
#include <cstring>

InfoView::InfoView() : infoWin(nullptr) {
    initInfoScreen();
}

InfoView::~InfoView() {
    if (infoWin != nullptr) {
        delwin(infoWin);
    }
}

void InfoView::initInfoScreen() {
    initscr(); // Initialize the screen
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input characters
    curs_set(0); // Hide the cursor

    int height = 20, width = 60;
    int startY = (LINES - height) / 2, startX = (COLS - width) / 2;

    infoWin = newwin(height, width, startY, startX);
    box(infoWin, 0, 0); // Draw a box around the window
    wrefresh(infoWin);
}

void InfoView::showInfo() const {
    werase(infoWin);
    box(infoWin, 0, 0);

    const char* title = "Welcome to Space Skirmish!";
    const char* description = "This game is a modern take on classic arcade games. "
                              "You  control a ship and must destroy incoming alien ships "
                              "before they reach the bottom of the screen."
                              "See if you can reach seeing all 6 distinct colors for alien ships!";
    const char* controls = "Controls: Arrow keys to move, Space to shoot, ESC to      return to the main menu.";

    // Adjust the starting Y position for the description and controls to ensure they don't overlap with the border
    int titleY = 2; // Start the title a bit lower to give top border clearance
    int descriptionY = titleY + 2; // Position the description below the title
    int controlsY = descriptionY + 6; // Position the controls below the description, adjust as needed based on description length
    int returnPromptY = 18; // Position the return prompt above the bottom border

    mvwprintw(infoWin, titleY, (70 - strlen(title)) / 2, "%s", title);
    mvwprintw(infoWin, descriptionY, 3, "%s", description); // Start a bit further from the left border
    mvwprintw(infoWin, controlsY, 3, "%s", controls); // Ensure controls are well-positioned
    mvwprintw(infoWin, returnPromptY, 3, "Press any key to return...");

    wrefresh(infoWin);
    wgetch(infoWin);  // Wait for user input
}