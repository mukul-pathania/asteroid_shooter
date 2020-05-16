#include <stdlib.h>
#include "collision.h"
#include "blast.h"
#include "FX.h"
#include <math.h>
#include <allegro5/allegro5.h>
#include "sounds.h"
#include "bgspace.h"
#include "spaceship.h"


/*Two circles are provided to this function and it returns true if they collide and false otherwise.
 */
bool is_colliding(BOUNDING_CIRCLE* circle1, BOUNDING_CIRCLE* circle2){
    float dx, dy, distance;
    dx = circle1->x - circle2->x;
    dy = circle1->y - circle2->y;
    distance = sqrt(dx*dx + dy*dy);
    if(distance < (circle1->radius + circle2->radius))
        return true;
    return false;
}


/*This function handles the collisions between the asteroids and the blasts and returns the number 
 *of collsions and 0 if no collisions took place.
 */
int check_and_handle_collisions(){
    int num_of_collisions = 0;

    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){
        if(blasts[i].gone)//condition is true if blast is not on screen
            continue;

        for(int j = 0; j < MAX_ASTEROID_COUNT; j++){
            if(asteroids[j].gone)//condition is true if the asteroid is not on screen
                continue;
            if(is_colliding(&blasts[i].circle, &asteroids[j].circle)){
                asteroids[j].life--;
                play_exp1sound();
                if(asteroids[j].life){
                    play_exp1sound(); 
                    FX_add(true, blasts[i].x, blasts[i].y);
                }
                else{
                    FX_add(false, asteroids[j].x, asteroids[j].y);
                    play_exp2sound();
                }
                if(!asteroids[j].life)
                   play_exp2sound();
                blasts[i].gone = true;
                blasts_on_screen--;
                num_of_collisions++;
            }
        }
    }
    return num_of_collisions;
}

void check_for_collision(){
    for (int i=0; i<MAX_COMET_COUNT; i++){
        if(comets[i].gone)
           continue;
        if(is_colliding(&comets[i].circle, &ship->circle)){
          ship->life --;
          comets[i].gone = true;
          comet_count--;
        }
    }
} 

void check_for_collision2(){

    for(int j = 0; j < MAX_ASTEROID_COUNT; j++){
            if(asteroids[j].gone)
               continue;
            if(is_colliding(&ship->circle, &asteroids[j].circle)){ 
                 ship->life = 0;
                 asteroids[j].gone = true;
                 play_exp2sound();
                 asteroid_count-- ;
            }
    }
}












