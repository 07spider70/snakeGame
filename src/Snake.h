#ifndef _SNAKE_H
#define _SNAKE_H

#include "mbed.h"
#include "CommonsSets.h"
#include <vector>
#include <string>

class Snake {

    public:
        Snake(COORD position, int speed);

        void setDirection(Direction dir);
        void growUp();
        COORD getPosition();
        vector<COORD> getBody();
        void moveSnake();
        
        bool collided();
        bool eatApple(COORD apple);
    
    private:
        COORD position;
        int speed;
        Direction dir;
        vector<COORD> body;
        int length;



};

#endif