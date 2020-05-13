#include "asteroid.h"
#include "spaceship.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "sounds.h"

ALLEGRO_BITMAP *SPRITESHEET, *SHIP ,*TRAIL ,*TRAILS[5];
SPACESHIP *ship;
ALLEGRO_TRANSFORM ship_transform;
extern ALLEGRO_DISPLAY *disp;
extern void must_init(bool, const char *);

void init_ship(){

    ship = (SPACESHIP*)malloc(sizeof(SPACESHIP));
    must_init(ship, "ship struct");

    SPRITESHEET = al_load_bitmap("resources/spritesheet.png");
    must_init(SPRITESHEET, "spritesheet");
    SHIP = al_create_sub_bitmap(SPRITESHEET, 0, 0, 12, 13);
    must_init(SHIP, "ship bitmap");
    TRAIL = al_load_bitmap("resources/trail.png");
    must_init(TRAIL, "trail bitmap");
    for(int i = 0; i < 5; i++){
        TRAILS[i] = al_create_bitmap(20, 20);
        must_init(TRAILS[i], "TRAILS[]");
    }
    al_set_target_bitmap(TRAILS[0]);
    al_draw_scaled_bitmap(TRAIL, 642, 45, 147, 160, 0, 0, 20, 20, 0);
    al_set_target_bitmap(TRAILS[1]);
    al_draw_scaled_bitmap(TRAIL, 437, 60, 121, 138, 0, 0, 20, 20, 0);
    al_set_target_bitmap(TRAILS[2]);
    al_draw_scaled_bitmap(TRAIL, 245, 106, 106, 85, 0, 0, 20, 20, 0);
    al_set_target_bitmap(TRAILS[3]);
    al_draw_scaled_bitmap(TRAIL, 232, 232, 121, 124, 0, 0, 20, 20, 0);
    al_set_target_bitmap(TRAILS[4]);
    al_draw_scaled_bitmap(TRAIL, 655, 222, 88, 70, 0, 0, 20, 20, 0);

    al_set_target_bitmap(al_get_backbuffer(disp));




    ship->x = (float)SCREEN_WIDTH / 2;
    ship->y = (float)SCREEN_HEIGHT / 2;
    ship->speed = 0;
    ship->heading = 0;
    ship->scale = 2;
    ship->is_drifting = false;


}


void draw_ship(SPACESHIP *ship){
    al_build_transform(&ship_transform, ship->x, ship->y, ship->scale,
            ship->scale, ship->heading);
    al_use_transform(&ship_transform);
    al_draw_bitmap(SHIP, -12/2, -13/2, 0);
    if(key[ALLEGRO_KEY_UP]){
        al_draw_bitmap(TRAILS[rand() % 5], -9, 13/2, 0);
    }
}

void deinit_ship(){
    al_destroy_bitmap(SPRITESHEET);
    al_destroy_bitmap(SHIP);
    al_destroy_bitmap(TRAIL);
    al_destroy_bitmap(TRAILS[0]);
    al_destroy_bitmap(TRAILS[1]);
    al_destroy_bitmap(TRAILS[2]);
    al_destroy_bitmap(TRAILS[3]);
    al_destroy_bitmap(TRAILS[4]);
}

void ship_update(SPACESHIP *ship){

    static float temp_heading;// for producing the drifting effect.
    static int sound_interval = 0; //for proper playing of rocket's trail sound.

    if(ship->speed > 0){
        ship->speed *= 0.95;
        if(ship->speed < 0.5)
            ship->speed = 0;
    }
    if(key[ALLEGRO_KEY_UP]){
        if(ship->speed == 0)
            ship->speed = 1;
        ship->speed *= SPACESHIP_ACC_GRADIENT;
        if(sound_interval == 0){
            play_tsound();//play the trail sound.
            sound_interval = 100;
        }
        else
            sound_interval--;
    }
    //if the ship is not acclerating.
    else{
        sound_interval = 0;
        al_stop_sample(&trail_id);
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
