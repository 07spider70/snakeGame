#include "Snake.h"


Snake::Snake(COORD position, int speed) {
    position = position;
    speed = speed;
    dir = LEFT;
    length = 1;

    body.push_back(position);
}


void Snake::setDirection(Direction dir) {
    dir = dir;
}

void Snake::growUp() {
    length++;
}
COORD Snake::getPosition() {
    return position;
}

vector<COORD> Snake::getBody() {
    return body;
}

void Snake::moveSnake() {
    switch (dir) {
        case UP:
            position.y -= speed;
            break;
        case DOWN:
            position.y += speed;
            break;
        case LEFT:
            position.x -= speed;
            break;
        case RIGHT:
            position.x += speed;
            break;
        default:
            break;
    }

    body.push_back(position);
    if(body.size() > length) {
        body.erase(body.begin());
    }
}
        
bool Snake::collided() {
    if(position.x < 1 || position.x > DISPLAY_WIDTH - 2 || position.y < 1 || position.y > DISPLAY_HEIGHT-2) {
        return true;
    }

    for(int i = 0; i< length-1; i++) {
        if(position.x == body[i].x && position.y == body[i].y) {
            return true;
        }
    }
    return false;
}
bool Snake::eatApple(COORD apple) {
    if(position.x == apple.x && position.y == apple.y) {
        return true;
    }

    return false;
}