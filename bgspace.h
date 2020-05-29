#ifndef FILE_BGSPACE_SEEN
#define FILE_BGSPACE_SEEN 1

#include <allegro5/allegro5.h>
#include "collision.h"
#include "asteroid.h"

extern ALLEGRO_DISPLAY* disp; //The main display of the game.

/*All of the background will be controlled through these functions.*/
void init_bgspace();
void update_bgspace();
void trigger_bgspace();
void draw_bgspace();
void destroy_bgspace();


/*The struct containing the information of the stars.*/
typedef struct{
    float x,y;
    float speed;
}STAR;

#define STAR_COUNT SCREEN_WIDTH / 2
extern STAR stars[STAR_COUNT];


/*Code for comets in the background*/
extern ALLEGRO_BITMAP *COMET;
/*This struct will contain all the info of the comets*/
typedef struct{
    float x,y,scale,speed;
    bool gone;
    BOUNDING_CIRCLE circle;
}COMETS;

#define MAX_COMET_COUNT 15
extern COMETS comets[MAX_COMET_COUNT];
extern int comet_count;
#define COMET_SPAWN_RATE 20

/*Below declarations handle the moving planets in the background.*/
extern ALLEGRO_BITMAP *PLANET_BITMAP , *PLANETS[5];
typedef struct{
    float x;
    float y;
    float speed;
    ALLEGRO_BITMAP *bmp;
    bool gone;
}PLANET;

#define MAX_PLANETS 3
#define PLANET_SPAWN_RATE 190
extern PLANET planets[MAX_PLANETS];
extern int planets_on_screen;
extern ALLEGRO_TRANSFORM planet_transform;


#endif //bgspace.h
