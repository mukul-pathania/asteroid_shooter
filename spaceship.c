#include "asteroid.h"
#include "spaceship.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

ALLEGRO_BITMAP *SPRITESHEET, *SHIP;
SPACESHIP *ship;
ALLEGRO_TRANSFORM ship_transform;

void init_ship(){
    
    ship = (SPACESHIP*)malloc(sizeof(SPACESHIP));
    
    SPRITESHEET = al_load_bitmap("spritesheet.png");
    if(!SPRITESHEET){
        fprintf(stderr, "Couldn't load Spritesheet");
        exit(1);
    }
    SHIP = al_create_sub_bitmap(SPRITESHEET, 0, 0, 12, 13);
    if(!SHIP){
        fprintf(stderr, "Couldn't load Ship");
        exit(1);
    }
    ship->x = (float)SCREEN_WIDTH / 2;
    ship->y = (float)SCREEN_HEIGHT / 2;
    ship->speed = 0;
    ship->heading = 0;
    ship->scale = 3;
    ship->is_drifting = false;


}


void draw_ship(SPACESHIP *ship){
    al_build_transform(&ship_transform, ship->x, ship->y, ship->scale, 
            ship->scale, ship->heading);
    al_use_transform(&ship_transform);
    al_draw_bitmap(SHIP, -12/2, -13/2, 0);
}

void ship_update(SPACESHIP *ship){
    
    static float temp_heading;

    if(ship->speed > 0){
        ship->speed *= 0.95;
        if(ship->speed < 0.5)
            ship->speed = 0;
    }
    if(key[ALLEGRO_KEY_UP]){
        if(ship->speed == 0)
            ship->speed = 1;
        ship->speed *= SPACESHIP_ACC_GRADIENT;
    }
    if(ship->speed > MAX_SPACESHIP_SPEED)
        ship->speed = MAX_SPACESHIP_SPEED;

    if(key[ALLEGRO_KEY_DOWN]){
        if(ship->speed > 1)
           ship->speed /= SPACESHIP_BRAKE_GRADIENT;
        else
            ship->speed = 0;
    }
    
    if((!key[ALLEGRO_KEY_UP]) && (ship->speed > 0))
        ship->is_drifting = true;
    else
        ship->is_drifting = false;

    if(!ship->is_drifting)
        temp_heading = ship->heading;
    
    if(key[ALLEGRO_KEY_LEFT]) 
        ship->heading -= MAX_TURN_RATE;
    
    if(key[ALLEGRO_KEY_RIGHT])
       ship->heading += MAX_TURN_RATE;


    float dx, dy;
    dx = sin(temp_heading) * ship->speed;
    dy = cos(temp_heading) * ship->speed;
    ship->x += dx;
    ship->y -= dy;
    if(ship->x > SCREEN_WIDTH)
        ship->x = 0;
    if(ship->x < 0)
        ship->x = SCREEN_WIDTH;
    if(ship->y < 0)
        ship->y = SCREEN_HEIGHT;
    if(ship->y > SCREEN_HEIGHT)
        ship->y = 0;


}
