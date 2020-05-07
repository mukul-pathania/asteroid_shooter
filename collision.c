#include "collision.h"
#include <math.h>

bool is_colliding(BOUNDING_CIRCLE* circle1, BOUNDING_CIRCLE* circle2){
    int distance = sqrt(pow(circle1.x - circle2.x, 2) + 
            pow(circle1.y - circle2.y, 2));
    if(circle1.radius + circle2.radius < distance)
        return false;
    return true;
}

