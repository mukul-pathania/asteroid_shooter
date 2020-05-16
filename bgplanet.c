#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"


ALLEGRO_BITMAP *PLANET , *PLANETS[5];
ALLEGRO_DISPLAY* disp;
bool planet_gone;
float x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;

void must_init(bool test, const char *description);

void init_planets(){
   PLANET = al_load_bitmap("resources/planet.png");
   if(!PLANET){
     fprintf(stderr, "Couldn't load Planet");
     exit(1);
   }

   PLANETS[0] = al_create_bitmap(180, 135);
   must_init(PLANETS[0], "PLANET[]");
   PLANETS[1] = al_create_bitmap(130, 135);
   must_init(PLANETS[1], "PLANET[]");
   PLANETS[2] = al_create_bitmap(120, 120);
   must_init(PLANETS[2], "PLANET[]");
   PLANETS[3] = al_create_bitmap(130, 130);
   must_init(PLANETS[3], "PLANET[]");
   PLANETS[4] = al_create_bitmap(90, 90);
   must_init(PLANETS[4], "PLANET[]");

   al_set_target_bitmap(PLANETS[0]);
   al_draw_scaled_bitmap(PLANET, 350, 65, 135, 135, 0, 0, 135, 135, 0);
   al_set_target_bitmap(PLANETS[1]);
   al_draw_scaled_bitmap(PLANET, 500, 70, 130, 135, 0, 0, 130, 135, 0);
   al_set_target_bitmap(PLANETS[2]);
   al_draw_scaled_bitmap(PLANET, 365, 230, 110, 110, 0, 0, 120, 120, 0);
   al_set_target_bitmap(PLANETS[3]);
   al_draw_scaled_bitmap(PLANET, 495, 210, 140, 140, 0, 0, 130, 130, 0);
   al_set_target_bitmap(PLANETS[4]);
   al_draw_scaled_bitmap(PLANET, 530, 377, 90, 90, 0, 0, 90, 90, 0);

   al_set_target_bitmap(al_get_backbuffer(disp));
   x1 = 100, x2 = 500; x3 = 800, x4 = 100;
   y1 = 200 ,y2 = 400, y3 = 0, y4 = -100;


}

void draw_planets(){

  al_draw_bitmap(PLANETS[0], x1, y1, 0);
  al_draw_bitmap(PLANETS[3], x2, y2, 0);
  al_draw_bitmap(PLANETS[4], x3, y3, 0);

  if(y1 >= SCREEN_HEIGHT-135){
    al_draw_bitmap(PLANETS[0], x1, y1, 0);
    al_draw_bitmap(PLANETS[0], x1, y1-SCREEN_HEIGHT, 0);
  }
  if(y2 >= SCREEN_HEIGHT-140){
      al_draw_bitmap(PLANETS[3], x2, y2, 0);
      al_draw_bitmap(PLANETS[3], x2, y2-SCREEN_HEIGHT, 0);
  }
  if(y3 >= SCREEN_HEIGHT-90){
        al_draw_bitmap(PLANETS[4], x3, y3, 0);
        al_draw_bitmap(PLANETS[4], x3, y3-SCREEN_HEIGHT, 0);
  }

}


void update_planets(){
   planet_gone = false;
   if(y1 >= SCREEN_HEIGHT){
     y1 -= SCREEN_HEIGHT;
 }
   if(y2 >= SCREEN_HEIGHT){
     y2 -= SCREEN_HEIGHT;
   }
   if(y3 >= SCREEN_HEIGHT){
     y3 -= SCREEN_HEIGHT;
   }
   y1+=1.8;
   y2+=1;
   y3+=2.5;

}
