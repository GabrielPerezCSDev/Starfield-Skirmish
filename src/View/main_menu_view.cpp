#include "View/main_menu_view.h"
#include <cstring>

MainMenuView::MainMenuView() : menuWin(nullptr) {
    initMenu();
}

MainMenuView::~MainMenuView() {
    endwin();
}

void MainMenuView::initMenu() {
    if (menuWin != nullptr) {
        delwin(menuWin);  // Delete the existing window if it exists
    }

    initscr(); // Initialize the screen, necessary if endwin() was previously called
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input characters
    curs_set(0); // Hide the cursor

    // Calculate window size and position
    int height = 10, width = 40;
    int startY = (LINES - height) / 2, startX = (COLS - width) / 2;

    menuWin = newwin(height, width, startY, startX);
    box(menuWin, 0, 0); // Draw a box around the window
    wrefresh(menuWin);
}

void MainMenuView::drawMenu() {
    const char* title = "Space Invaders";
    const char* options[] = {"Start Game", "Info", "Quit Game"};
    int numOptions = sizeof(options) / sizeof(char*);

    // Print the title
    mvwprintw(menuWin, 1, (40 - strlen(title)) / 2, "%s", title);

    // Print the options
    for (int i = 0; i < numOptions; ++i) {
        mvwprintw(menuWin, i + 3, 10, "%s", options[i]);
    }

    wrefresh(menuWin);
}

int MainMenuView::handleInput() {
    int choice = 0;
    int highlight = 0;
    keypad(menuWin, TRUE); // Enable keyboard input for the window

    while (true) {
        for (int i = 0; i < 3; ++i) {
            if (i == highlight)
                wattron(menuWin, A_REVERSE);
            mvwprintw(menuWin, i + 3, 10, "%s", i == 0 ? "Start Game" : i == 1 ? "Info" : "Quit Game");
            wattroff(menuWin, A_REVERSE);
        }
        choice = wgetch(menuWin);

        switch (choice) {
            case KEY_UP:
                highlight = (highlight - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % 3;
                break;
            case 10: // Enter key
                return highlight;
        }
    }
}

int MainMenuView::showMenu() {
    initMenu();  // Reinitialize the menu window and draw the box
    drawMenu();
    return handleInput();
}