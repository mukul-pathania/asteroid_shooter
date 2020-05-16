#include <allegro5/allegro_image.h>
#include "asteroid.h"
#include <math.h>
#include "planets.h"
#include <stdio.h>
#include <stdlib.h>
//#include <allegro5/allegro_primitives.h>

ALLEGRO_BITMAP  *COMET, *comet;
COMETS comets[MAX_COMET_COUNT];
extern ALLEGRO_DISPLAY *disp;
int i,comet_count=0;
void init_planet(){

       comet = al_load_bitmap("resources/comet.png");
     if(!comet){
        printf("Couldn't load comet");
        exit(1);
     }

     for(i=0;i<MAX_COMET_COUNT;i++){
        comets[i].gone = true;
     }
     COMET = al_create_bitmap(20,20);
     al_set_target_bitmap(COMET);
     al_draw_scaled_bitmap(comet, 0, 0,508,508, 0, 0,20,20,0);
     al_set_target_bitmap(al_get_backbuffer(disp));
}


static void create_comet(COMETS *com){


       com->x =rand() % SCREEN_WIDTH;
       com->y = rand() % SCREEN_HEIGHT;

       com->speed = 2;
       com->scale = 2;
       com->gone = false;
       comet_count++;

}


void destroy_planet(){
     al_destroy_bitmap(comet);
}

void update_comet(){

     for(i=0; i<MAX_COMET_COUNT; i++){
        if(comets[i].gone)
          continue;

        comets[i].x -= comets[i].speed;
        comets[i].y += comets[i].speed;


        if (comets[i].x > SCREEN_WIDTH || comets[i].x < 0 || comets[i].y >
           SCREEN_HEIGHT || comets[i].y < 0 ){
           comet_count--;
           comets[i].gone = true;
        }
    }
}

static void draw_comet(COMETS *c){
     al_draw_bitmap(COMET, c->x,c->y, 0);
}

void draw_comets(){
    for(i=0;i<MAX_COMET_COUNT;i++){
       if(!comets[i].gone)
          draw_comet(&comets[i]);
    }
}

void create_new_comet(){
     for(i=0;i<MAX_COMET_COUNT;i++){
        if(comets[i].gone){
           create_comet(&comets[i]);
           return;
        }
     }
}

void trigger_comet(){
    if (comet_count < MAX_COMET_COUNT )
       create_new_comet();
}
