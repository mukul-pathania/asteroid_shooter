#include <allegro5/allegro5.h>
#define MAX_COMET_COUNT 10
extern ALLEGRO_BITMAP  *COMET;

typedef struct{
    float x,y,scale,speed;
    bool gone;
}COMETS;

extern COMETS comets[MAX_COMET_COUNT];
extern int comet_count;


void init_planet();
void destroy_planet();
void update_comet();
static void create_comet(COMETS *comet);
static void draw_comet(COMETS *comet);
void draw_comets();
static void create_new_comet();
void trigger_comet();
