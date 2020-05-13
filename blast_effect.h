#include <allegro5/allegro5.h>

#define EFFECT_N 130
#define EXPLOSION_FRAMES 8
#define SPARKS_FRAMES 4

typedef struct EFFECT{
  int x,y;
  int frame;
  bool spark;
  bool used;
}EFFECT;

extern EFFECT effect[EFFECT_N];
extern ALLEGRO_BITMAP *SPARK[SPARKS_FRAMES], *EXPLOSION[EXPLOSION_FRAMES], *EXPLOSION_IMG, *SPARK_IMG;
extern ALLEGRO_DISPLAY* disp;

void effect_init();
void effect_add(bool, int, int);
void effect_draw();
void effect_update();
void deinit_effect();
