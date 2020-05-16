#include <allegro5/allegro5.h>
#include "asteroid.h"

#define STAR_COUNT SCREEN_WIDTH / 2

typedef struct{
     float x,y;
     float speed;
}STAR;

extern STAR stars[STAR_COUNT];

void init_star();
void star_update();
void star_create();
