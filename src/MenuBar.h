
#ifndef _MENUBAR_H
#define _MENUBAR_H

#include <string>
#include "mbed.h"
#include "LCD_DISCO_L476VG.h"
class MenuBar
{

private:
    typedef enum {
        START,
        HIGH_SCORE,
        RESET,
        RUNNING
    } mainMenu;


public:
    MenuBar(LCD_DISCO_L476VG* menuDisplay );
    void init();
    void butClicked(PinName joyBut);
    void addPoint();
    int getHighScore();
    bool isGameRunning();
    void gameStopped();

private:
    void next();
    void back();
    void accept();
    void decline();
    void refresh();


private:
    int _actualScore;
    int _highScore;
    bool askReset;
    bool gameRun;
    bool showScore;

    mainMenu _actualMenu;
    LCD_DISCO_L476VG* _display;
    string stringToDispl;
    uint8_t DisplayedString[];
};

#endif
