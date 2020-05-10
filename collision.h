#ifndef FILE_COLLISION_SEEN
#include<allegro5/allegro5.h>
#define FILE_COLLISION_SEEN 1

typedef struct{
    float x, y, radius;
}BOUNDING_CIRCLE;

bool is_colliding(BOUNDING_CIRCLE* circle1, BOUNDING_CIRCLE* circle2);
int check_and_handle_collisions();

#endif
