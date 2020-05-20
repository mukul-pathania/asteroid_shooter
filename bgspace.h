#ifndef FILE_BGSPACE_SEEN
#define FILE_BGSPACE_SEEN 1

#include <allegro5/allegro5.h>
#include "collision.h"
#include "asteroid.h"

extern ALLEGRO_DISPLAY* disp; //The main display of the game.

void init_bgspace();
void update_bgspace();
void trigger_bgspace();
void draw_bgspace();


/*The struct containing the information of the stars.*/
typedef struct{
     float x,y;
     float speed;
}STAR;

#define STAR_COUNT SCREEN_WIDTH / 2
extern STAR stars[STAR_COUNT];
//extern ALLEGRO_TRANSFORM comet_transform;
/*These three functions handle the drawing of stars in the background.*/
static void init_star();
static void update_star();
static void draw_star();


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
/*These functions handle all the aspects of comets*/
static void create_comet(COMETS *comet);
static void draw_comet(COMETS *comet);
static void draw_comets();
static void create_new_comet();
static void trigger_comet();
static void init_comet();
void destroy_comet();
static void update_comet();

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
#define PLANET_SPAWN_RATE 150
extern PLANET planets[MAX_PLANETS];
extern int planets_on_screen;
extern ALLEGRO_TRANSFORM planet_transform;
static void init_planets();
static void trigger_planet();
static void create_planet();
static void draw_planets();
static void update_planets();


#endif //bgspace.h
