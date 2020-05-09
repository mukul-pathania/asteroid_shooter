#include <math.h>
#include "bgspace.h"

STAR stars[STAR_COUNT];

void init_star(){

    for(int i=0; i < STAR_COUNT ; i++){
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_HEIGHT ;
        //stars[i].speed = 0;
        stars[i].dy = 0;
    }
}

void star_update(){

    for(int i=0; i < STAR_COUNT; i++){

       if(stars[i].dy==0){
          stars[i].dy = 1;
          //stars[i].speed *= 0.95;
       }else{
          stars[i].dy = 1.2;
       }
       
       /*if(stars[i].speed > 20){
          stars[i].speed = 0;
       }
       
       if(stars[i].speed < 0){
          stars[i].speed = 0;
       }
       
       //star[i].dy = star[i].speed*/
       stars[i].y += stars[i].dy;
       if (stars[i].y > SCREEN_HEIGHT){
          stars[i].y = 0;
          //stars[i].speed = 0;
       }
    }
}

void star_create(){
  
    for(int i=0; i < STAR_COUNT; i++){
        al_draw_pixel(stars[i].x , stars[i].y, al_map_rgb(0,255,0));
        //stars[i].x +=2;
    }
}
           
