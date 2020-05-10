#include <stdlib.h>
#include "collision.h"
#include "asteroid.h"
#include "blast.h"
#include <math.h>
#include <allegro5/allegro5.h>

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
    int num_collisions = 0;
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){
        if(blasts[i].gone)//condition is true if blast is not on screen
            continue;

        for(int j = 0; j < MAX_ASTEROID_COUNT; j++){
            if(asteroids[j].gone)//condition is true if the asteroid is not on screen
                continue;
            if(is_colliding(&blasts[i].circle, &asteroids[j].circle)){
                asteroids[j].life--;
                blasts[i].gone = true;
                blasts_on_screen--;
            }
        }
    }
    return num_collisions;
}
                
            
            

