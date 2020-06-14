#ifndef FILE_MAIN_SEEN

#define FILE_MAIN_SEEN 1
#include <allegro5/allegro5.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 640

#define DEG_TO_RAD(x) ((float) (x)*ALLEGRO_PI/180)
#define FLIP_COIN(x, y) (( rand() % 2) ? (x) : (y))
#define RAND_DOUBLE_RANGE(min, max) ((float)rand() / (float) (RAND_MAX / (max - min)) + min)

extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_DISPLAY* disp;
extern bool done, menu;

void destroy_main();
void game_loop();
void reload_ship();
void must_init(bool, const char*);

#endif //main.h
