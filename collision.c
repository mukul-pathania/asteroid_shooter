#include <stdlib.h>
#include "collision.h"
#include "asteroid.h"
#include "blast.h"
#include <math.h>
#include <allegro5/allegro5.h>

bool is_colliding(BOUNDING_CIRCLE* circle1, BOUNDING_CIRCLE* circle2){
    float dx, dy, distance;
    dx = circle1->x - circle2->x;
    dy = circle1->y - circle2->y;
    distance = sqrt(dx*dx + dy*dy);
    if(distance < (circle1->radius + circle2->radius))
        return true;
    return false;
}

bool check_collision(){
    for(int i = 0; i < MAX_BLASTS_ON_SCREEN; i++){
        if(blasts[i].gone)
            continue;

        for(int j = 0; j < MAX_ASTEROID_COUNT; j++){
            if(asteroids[j].gone)
                continue;
            if(is_colliding(&blasts[i].circle, &asteroids[j].circle)){
                return true;
            }
        }
    }
    return false;
}
                
            
            

