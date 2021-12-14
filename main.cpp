#include "mbed.h"
#include "LCD_DISCO_L476VG.h"
#include "MenuBar.h"
// Joystick button
InterruptIn center(JOYSTICK_CENTER);
InterruptIn left(JOYSTICK_LEFT);
InterruptIn right(JOYSTICK_RIGHT);
InterruptIn up(JOYSTICK_UP);
InterruptIn down(JOYSTICK_DOWN);

DigitalOut led_green(LED1);
DigitalOut led_red(LED2);

volatile bool butUp = false;
volatile bool butDown = false;
volatile bool butLeft = false;
volatile bool butRight = false;
volatile bool butCenter = false;
volatile bool stopGame = false;
bool gameRun = false;

void center_pressed() {
    butCenter = true;  
    led_green = 1;
}

void up_pressed() {
    butUp = true;  
    led_green = 1;
}

void down_pressed() {
    butDown = true;  
    led_green = 1;
}

void left_pressed() {
    butLeft = true;  
    led_green = 1;
}

void right_pressed() {
    butRight = true;  
    led_green = 1;
}

void endGame() {
    stopGame = true;
}

int main() {
    LCD_DISCO_L476VG lcd;
    lcd.Clear();

    center.rise(&center_pressed);
    left.rise(&left_pressed);
    right.rise(&right_pressed);
    up.rise(&up_pressed);
    down.rise(&down_pressed);

    left.mode(PullDown);
    right.mode(PullDown);
    up.mode(PullDown);
    down.mode(PullDown);

    MenuBar glass(&lcd);

    Timeout gameEnd;

    while(true) {

        if(glass.isGameRunning()) {
            if(!gameRun ) {
                gameEnd.attach(&endGame, 5s);
                gameRun = true;
            }
            if(stopGame) {
                glass.gameStopped();
                gameEnd.detach();
                stopGame= false;
                gameRun = false;
            }
        }

            
     
            if(butUp) {
                glass.butClicked(JOYSTICK_UP);
                butUp = false;
                led_green = 0;
            } else if(butDown) {
                glass.butClicked(JOYSTICK_DOWN);
                butDown = false;
                led_green = 0;
            } else if(butRight) {
                glass.butClicked(JOYSTICK_RIGHT);
                butRight = false;
                led_green = 0;
            } else if(butLeft) {
                glass.butClicked(JOYSTICK_LEFT);
                butLeft = false;
                led_green = 0;
            }else if(butCenter) {
                glass.butClicked(JOYSTICK_CENTER);
                butCenter = false;
                led_green = 0;
            }
        

        ThisThread::sleep_for(200ms);
    }

}