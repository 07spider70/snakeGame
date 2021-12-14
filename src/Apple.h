#ifndef _APPLE_H
#define _APPLE_H

#include "mbed.h"
#include "CommonsSets.h"
#include <vector>
#include <string>

class Apple {

public:
    Apple();
    
    void spawnApple();
    COORD getPosition();
private:
    COORD position;

};

#endif