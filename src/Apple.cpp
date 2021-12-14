#include "Apple.h"

Apple::Apple() {
    position.x = -1;
    position.y = -1;
}

void Apple::spawnApple() {
    position.x = (rand() % DISPLAY_WIDTH - 3 ) + 1;
    position.y = (rand() % DISPLAY_HEIGHT - 3 ) + 1;
}

COORD Apple::getPosition() {
    return position;
}