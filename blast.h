#include "collision.h"
#define MAX_BLASTS_ON_SCREEN 40
#define FRAME_INTERVAL_BETWEEN_BLASTS 4
#define BLAST_LENGTH 6
#define BLAST_WIDTH 2
#define BLAST_SPEED 25
extern int blasts_on_screen;
typedef struct{
    float x, y, heading, speed, scale;
    bool gone;
    BOUNDING_CIRCLE circle;
    ALLEGRO_COLOR color;
}BLAST;

extern ALLEGRO_TRANSFORM blast_transform;
extern BLAST blasts[MAX_BLASTS_ON_SCREEN];
void init_blasts();
void create_blast(BLAST *blast);
void create_new_blast();
void blast_trigger();
void update_blasts();
void draw_blast(BLAST* blast);
void draw_all_blasts();
