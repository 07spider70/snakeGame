#include "mbed.h"
#include "MenuBar.h"
#include <string>

MenuBar::MenuBar(LCD_DISCO_L476VG* menuDisplay) {
    _actualScore = 0;
    _highScore = 0;
    askReset = false;
    gameRun = false;
    showScore = false;

    _actualMenu = START;
    _display = menuDisplay;
    refresh();
}

void MenuBar::next() {
    switch(_actualMenu) {
        case(START):
            _actualMenu = HIGH_SCORE;
            break;
        case(HIGH_SCORE):
            _actualMenu = RESET;
            break;
        case(RESET):
            _actualMenu = START;
            break;
        case(RUNNING):
            break;
    }

    refresh();
}

void MenuBar::back() {
        switch(_actualMenu) {
        case(START):
            _actualMenu = RESET;
            break;
        case(HIGH_SCORE):
            _actualMenu = START;
            break;
        case(RESET):
            _actualMenu = HIGH_SCORE;
            break;
        case(RUNNING):
            break;
    }

    refresh();
}
bool MenuBar::isGameRunning() {
    return gameRun;
}

void MenuBar::gameStopped() {
    gameRun = false;
    _actualMenu = START;
    refresh();
}
void MenuBar::accept() {
        if(!askReset && !showScore){
        switch(_actualMenu) {
        case(START):
            //start game and show actual score
            gameRun = true;
            _actualMenu = RUNNING;
            _actualScore++;
            break;
        case(HIGH_SCORE):
            sprintf((char *)DisplayedString, "score: %d ", _highScore);
            stringToDispl = "score: " + to_string(_highScore) + " ";
            showScore = true;
            break;
        case(RESET):
            sprintf((char *)DisplayedString, "Really? ");
            stringToDispl = "Really? ";
            askReset = true;
            break;
        case(RUNNING):
            break;
    }} else if (askReset) {
        _highScore = 0;
        _actualScore = 0;
        _actualMenu = RESET;
        askReset = false;
    } else if (showScore) {
        _actualMenu = HIGH_SCORE;
        showScore = false;
    }
        

    refresh();
}

void MenuBar::decline() {
    showScore = false;
    askReset = false;
    refresh();
}

void MenuBar::refresh() {

    if(_actualScore > _highScore) {
        _highScore=_actualScore;
    }

    _display->Clear();
    if(showScore || askReset) {
         if(stringToDispl.length() > 6) {
         _display->ScrollSentence(DisplayedString,1, 250);
         } else {
            _display->DisplayString(DisplayedString);
        }
        return;
    }

    switch(_actualMenu) {
         case(START):
            sprintf((char *)DisplayedString, "Start ");
            stringToDispl = "Start ";
            break;
        case(HIGH_SCORE):
            sprintf((char *)DisplayedString, "HighScore ");
            stringToDispl = "HighScore ";
            break;
        case(RESET):
            sprintf((char *)DisplayedString, "Reset ");
            stringToDispl = "Reset ";
            break;
        case(RUNNING):
            sprintf((char *)DisplayedString, "RUN ");
            stringToDispl = "RUN ";
            break;
    }

    if(stringToDispl.length() > 6) {
        _display->ScrollSentence(DisplayedString,1, 250);
    } else {
            _display->DisplayString(DisplayedString);
        }
    return;
}


void MenuBar::butClicked(PinName joyBut) {
    if(isGameRunning()) {
        return;
    }
    switch(joyBut) {
        case(JOYSTICK_CENTER): {
            accept();
            break;
        }

        case(JOYSTICK_LEFT): {
            back();
            break;
        }

        case(JOYSTICK_RIGHT): {
            next();
            break;
        }

        case(JOYSTICK_UP): {
            decline();
            break;
        }
        case(JOYSTICK_DOWN): {
            decline();
            break;
        }
        default: {
            return;
            break;
        }
    }
}
void MenuBar::addPoint() {
    _actualScore++;
}
int MenuBar::getHighScore() {
    return _highScore;
}