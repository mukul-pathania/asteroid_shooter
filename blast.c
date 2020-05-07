#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "blast.h"
#include "spaceship.h"
#include "input.h"
#include "asteroid.h"
#include <math.h>
#include "sounds.h"

int blasts_on_screen = 0;
BLAST blasts[MAX_BLASTS_ON_SCREEN];
ALLEGRO_TRANSFORM blast_transform;

void init_blasts(){
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++)
        blasts[i].gone = true;
}

void create_blast(BLAST *blast){
    blast->x = ship->x ;
    blast->y = ship->y ;
    blast->heading = ship->heading;
    //blast->speed = (ship->speed) ? (ship->speed * 2) : (5);
    blast->speed = (BLAST_SPEED > ship->speed * 2) ? (BLAST_SPEED) : (ship->speed * 2);
    blast->scale = 1;
    blast->gone = false;
    blast->color = al_map_rgb(255, 255, 255);
    blasts_on_screen++;
}

void create_new_blast(){
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++)
        if(blasts[i].gone){
            create_blast(&blasts[i]);
            return;
        }
}

void blast_trigger(){
    static int blast_interval = 0;
    if((key[ALLEGRO_KEY_SPACE]))
        if((blasts_on_screen < MAX_BLASTS_ON_SCREEN) && (blast_interval == 0)){ 
        create_new_blast();
        play_bsound();
        blast_interval = FRAME_INTERVAL_BETWEEN_BLASTS;
        }
    if(blast_interval > 0)
        blast_interval--;
}

void update_blasts(){
    float dx, dy;
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){

        if(blasts[i].gone)
            continue;

        dx = sin(blasts[i].heading) * blasts[i].speed;
        dy = -cos(blasts[i].heading) * blasts[i].speed;
        blasts[i].y += dy;
        blasts[i].x += dx;

        if(blasts[i].x < 0 || blasts[i].x > SCREEN_WIDTH || 
                blasts[i].y < 0 || blasts[i].y > SCREEN_HEIGHT){
            blasts[i].gone = true;
            blasts_on_screen--;
        }
    }
}

void draw_blast(BLAST* blast){
    al_build_transform(&blast_transform, blast->x, blast->y, blast->scale, blast->scale, blast->heading);
    al_use_transform(&blast_transform);
	al_draw_line(0, 0, 0, -BLAST_LENGTH, blast->color, BLAST_WIDTH);
}

void draw_all_blasts(){
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){
        
        if(blasts[i].gone)
            continue;

        draw_blast(&blasts[i]);
    }
}

