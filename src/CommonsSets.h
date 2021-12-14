#ifndef _COMMONSSETS_H
#define _COMMONSSETS_H

#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48 
#define SPEED_INCREASE_FACTOR 1 //speed increase after food eaten
#define INIT_SIZE 1 //init length of snake
#define MAX_SIZE 254 // max lenght of snake
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

typedef struct {
    unsigned char x;
    unsigned char y;
} COORD;

#endif