#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "blast.h"
#include "spaceship.h"
#include "input.h"
#include "main.h"
#include <math.h>
#include "sounds.h"

void must_init(bool , const char* );
static void create_blast(BLAST *blast);
static void create_new_blast();
static void draw_blast(BLAST* blast);

extern ALLEGRO_DISPLAY *disp;

int blasts_on_screen = 0;
BLAST blasts[MAX_BLASTS_ON_SCREEN];
ALLEGRO_TRANSFORM blast_transform;
ALLEGRO_BITMAP *BLAST_SHEET;
ALLEGRO_BITMAP *BLAST_IMG;

void init_blasts(){

    BLAST_SHEET = al_load_bitmap("resources/blast.png");
    must_init(BLAST_SHEET, "BLAST_SHEET");
    BLAST_IMG = al_create_bitmap(11, 30);
    must_init(BLAST_IMG, "BLAST_IMAGE");
    al_set_target_bitmap(BLAST_IMG);
    al_draw_scaled_bitmap(BLAST_SHEET, 125, 120, 11, 30, 0, 0, 11/1.3, 30/1.3, 0);
    al_set_target_bitmap(al_get_backbuffer(disp));

    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++)
        blasts[i].gone = true;
}

void destroy_blasts(){
    al_destroy_bitmap(BLAST_SHEET);
    al_destroy_bitmap(BLAST_IMG);
}


static void create_blast(BLAST *blast){
    blast->x = blast->circle.x = ship->x ;
    blast->y = blast->circle.y = ship->y ;
    blast->heading = ship->heading;
    blast->speed = (BLAST_SPEED > ship->speed * 2) ? (BLAST_SPEED) : (ship->speed * 2);
    blast->scale = 1;
    blast->gone = false;
    blast->circle.radius = 3; //only the tip of the blast is checked for collision
    blasts_on_screen++;
}

static void create_new_blast(){
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
        blasts[i].circle.y = (blasts[i].y += dy);
        blasts[i].circle.x = (blasts[i].x += dx);

        if(blasts[i].x < 0 || blasts[i].x > SCREEN_WIDTH ||
                blasts[i].y < 0 || blasts[i].y > SCREEN_HEIGHT){
            blasts[i].gone = true;
            blasts_on_screen--;
        }
    }
}

static void draw_blast(BLAST* blast){
    al_build_transform(&blast_transform, blast->x, blast->y, blast->scale, blast->scale, blast->heading);
    al_use_transform(&blast_transform);
    // al_draw_tinted_bitmap(BLAST_IMG, al_map_rgb(255, 0, 0), -5, 0, 0);
    al_draw_bitmap(BLAST_IMG, -5, 0, 0);
}

void draw_all_blasts(){
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){

        if(blasts[i].gone)
            continue;

        draw_blast(&blasts[i]);
    }
}

