#include <math.h>
#include "bgspace.h"

STAR stars[STAR_COUNT];

void init_star(){
    int x = 1;

    for(int i=0; i < STAR_COUNT ; i++, x += 2){
        stars[i].x = x;
        stars[i].y = rand() % SCREEN_HEIGHT ;
        stars[i].speed = RAND_DOUBLE_RANGE(0.1, 1.5);
    }
}

void star_update(){

    for(int i=0; i < STAR_COUNT; i++){

       stars[i].y += stars[i].speed;
       if (stars[i].y > SCREEN_HEIGHT){
          stars[i].y = 0;
       }
    }
}

void star_create(){
    float l;
  
    for(int i=0; i < STAR_COUNT; i++){
        l = stars[i].speed;
        al_draw_pixel(stars[i].x , stars[i].y, al_map_rgb(0, l * 255, l * 255));
    }
}
           
