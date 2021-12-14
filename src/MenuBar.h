
#ifndef _MENUBAR_H
#define _MENUBAR_H

#include <string>
#include "mbed.h"
#include "LCD_DISCO_L476VG.h"
#include "CommonsSets.h"

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
    MenuBar(LCD_DISCO_L476VG* menuDisplay, sharedStruct* sharedData );
    void init();
    void butClicked(Direction joyBut);
    void setScore(int sc);
    int getHighScore();
    bool isGameRunning();
    void gameStopped();
    void startGame();
    void menuThread();

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
    sharedStruct* sharedData;

    mainMenu _actualMenu;
    LCD_DISCO_L476VG* _display;
    string stringToDispl;
    uint8_t DisplayedString[];
};

#endif
