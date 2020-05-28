#ifndef FILE_SPACESHIP_SEEN
#define FILE_SPACESHIP_SEEN 1

#define MAX_SPACESHIP_SPEED 20
#define SPACESHIP_BRAKE_GRADIENT 1.2
#define SPACESHIP_ACC_GRADIENT 1.2
#define MAX_TURN_RATE DEG_TO_RAD(6)
#include "collision.h"

extern ALLEGRO_BITMAP *SPRITESHEET, *SHIP, *TRAIL, *TRAILS[5];

typedef struct{
    float x, y, speed, heading, scale;
    bool is_drifting;
    int life;
    BOUNDING_CIRCLE circle;
}SPACESHIP;

extern SPACESHIP *ship;
extern ALLEGRO_TRANSFORM ship_transform;
void init_ship();
void destroy_ship();
void draw_ship(SPACESHIP *ship);
void ship_update(SPACESHIP *ship);

#endif //spaceship.h
