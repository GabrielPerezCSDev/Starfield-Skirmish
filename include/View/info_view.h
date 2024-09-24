#ifndef INFO_VIEW_H
#define INFO_VIEW_H

#include <ncurses.h>

class InfoView {
public:
    InfoView();
    ~InfoView();
    void showInfo() const;

private:
    WINDOW* infoWin;
    void initInfoScreen();
};

#endif // INFO_SCREEN_H