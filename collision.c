#include <stdlib.h>
#include "collision.h"
#include "blast.h"
#include "FX.h"
#include <math.h>
#include <allegro5/allegro5.h>
#include "sounds.h"
#include "spaceship.h"
#include "asteroid.h"

/*Two circles are provided to this function and it returns true if
 *they collide and false otherwise.*/
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

    for(int i = 0; i < MAX_ASTEROID_COUNT; i++){
        if(asteroids[i].gone)//condition is true if asteroid is not on screen
            continue;

        for(int j = 0; j < MAX_BLASTS_ON_SCREEN; j++){
            if(blasts[j].gone)//condition is true if the blast is not on screen
                continue;
            //check for collision between the asteroid and the blast.
            if(is_colliding(&blasts[j].circle, &asteroids[i].circle)){
                asteroids[i].life--;
                play_exp1sound();
                if(asteroids[i].life){
                    play_exp1sound(); 
                    FX_add(true, blasts[j].x, blasts[j].y, 1);
                }
                else{
                    FX_add(false, asteroids[i].x, asteroids[i].y, asteroids[i].scale);
                    play_exp2sound();
                }
                blasts[j].gone = true;
                blasts_on_screen--;
                num_of_collisions++;
            }
        }

        /*If the respawn timer or invincibility timer is present then there
         *is no need to check for collison with the ship.*/
        if(ship->lives >= 0 && ship->invincible_timer == 0 && ship->respawn_timer == 0)
        {

            if(is_colliding(&asteroids[i].circle, &ship->circle)){
                ship->health = 0;
                FX_add(false, ship->x, ship->y, 1);
                FX_add(false, asteroids[i].x, asteroids[i].y, asteroids[i].scale);
                asteroids[i].gone = true;
                asteroid_count--;
                play_exp2sound();
                num_of_collisions++;
            }
        }


    }
    return num_of_collisions;
}

