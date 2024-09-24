#ifndef MAIN_MENU_VIEW_H
#define MAIN_MENU_VIEW_H

#include <ncurses.h>

class MainMenuView {
public:
    MainMenuView();
    ~MainMenuView();
    int showMenu(); // Displays the menu and returns the selected option

private:
    WINDOW* menuWin;
    void initMenu();
    void drawMenu();
    int handleInput();
};

#endif // MAIN_MENU_VIEW_H