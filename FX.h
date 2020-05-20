#ifndef FILE_FX_SEEN
#define FILE_FX_SEEN 1

#include <allegro5/allegro5.h>

#define FX_N 130
#define EXPLOSION_FRAMES 8
#define SPARKS_FRAMES 4

typedef struct FX{
  int x,y;
  int frame;
  bool spark;
  float scale;
  bool used;
}FX;

extern FX fx[FX_N];
extern ALLEGRO_BITMAP *SPARK[SPARKS_FRAMES], *EXPLOSION[EXPLOSION_FRAMES], *EXPLOSION_IMG, *SPARK_IMG;
extern ALLEGRO_DISPLAY* disp;

void FX_init();
void FX_add(bool, int, int, int);
void FX_draw();
void FX_update();
void deinit_FX();

#endif //FX.h
