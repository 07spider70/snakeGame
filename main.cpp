#include "mbed.h"
#include "LCD_DISCO_L476VG.h"
#include "MenuBar.h"
#include "CommonsSets.h"
#include "Mutex.h"


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
Timeout gameEnd;
Mutex dataMutex;
    //init empty struct for sharing data
sharedStruct sharedData = {};




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

void runMenuDisplay(MenuBar* disp) {
    disp->menuThread();
    ThisThread::sleep_for(50ms);
}

void endGame() {
        sharedData.changeSharedDataMut->lock();
        sharedData.gameIsRunning = false;
        sharedData.changeSharedDataMut->unlock();
        gameEnd.detach();
    }





int main() {
   // memset(&sharedData, 0, sizeof(sharedStruct));

    sharedData.changeSharedDataMut = &dataMutex;
    sharedData.actualMove = NONE;
    sharedData.gameIsRunning = false;
    sharedData.score = 0;
    Thread glassThread;
    LCD_DISCO_L476VG lcd;
    lcd.Clear();

    MenuBar glass(&lcd, &sharedData);

    center.rise(&center_pressed);
    left.rise(&left_pressed);
    right.rise(&right_pressed);
    up.rise(&up_pressed);
    down.rise(&down_pressed);

    left.mode(PullDown);
    right.mode(PullDown);
    up.mode(PullDown);
    down.mode(PullDown);

    
   glassThread.start(callback(runMenuDisplay, &glass));
    
    while(true) {

        sharedData.changeSharedDataMut->lock();
        if(sharedData.gameIsRunning) {
            gameEnd.attach(&endGame, 5s);
        }
        sharedData.changeSharedDataMut->unlock();

   
     
            if(butUp) {
                sharedData.changeSharedDataMut->lock();
                sharedData.actualMove = UP;
                sharedData.changeSharedDataMut->unlock();
                led_green = 0;
            } else if(butDown) {
                sharedData.changeSharedDataMut->lock();
                sharedData.actualMove = DOWN;
                sharedData.changeSharedDataMut->unlock();
                led_green = 0;
            } else if(butRight) {
                sharedData.changeSharedDataMut->lock();
                sharedData.actualMove = RIGHT;
                sharedData.changeSharedDataMut->unlock();
                led_green = 0;
            } else if(butLeft) {
                sharedData.changeSharedDataMut->lock();
                sharedData.actualMove = LEFT;
                sharedData.changeSharedDataMut->unlock();
                led_green = 0;
            }else if(butCenter) {
                sharedData.changeSharedDataMut->lock();
                sharedData.actualMove = CENTER;
                sharedData.changeSharedDataMut->unlock();
                led_green = 0;
            }
        

        ThisThread::sleep_for(200ms);
    }

}