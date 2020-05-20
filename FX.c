#include <stdlib.h>
#include <stdio.h>
#include "FX.h"


FX fx[FX_N];
ALLEGRO_BITMAP *SPARK[SPARKS_FRAMES], *EXPLOSION[EXPLOSION_FRAMES], *EXPLOSION_IMG, *SPARK_IMG;
void must_init(bool, const char *);
ALLEGRO_TRANSFORM FX_TRANSFORM;

void FX_init(){

    EXPLOSION_IMG = al_load_bitmap("resources/explosion.png");
    SPARK_IMG = al_load_bitmap("resources/sparks.png");

    must_init(EXPLOSION_IMG, "Explosion image");
    must_init(SPARK_IMG, "Sparks image");
    for(int i = 0; i < EXPLOSION_FRAMES; i++){
        EXPLOSION[i] = al_create_bitmap(80, 80);
        must_init(EXPLOSION[i], "EXPLOSION[]");
    }
    for(int i = 0; i < SPARKS_FRAMES; i++){
        SPARK[i] = al_create_bitmap(50, 50);
        must_init(SPARK[i], "SPARK[]");
    }

    al_set_target_bitmap(EXPLOSION[0]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 0, 135, 54, 45, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[1]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 129, 72, 52, 50, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[2]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 67, 72, 56, 50, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[3]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 0, 70, 55, 50, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[4]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 128, 3, 56, 54, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[5]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 0, 0, 54, 56, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[6]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 0, 135, 54, 45, 0, 0, 80, 80, 0);
    al_set_target_bitmap(EXPLOSION[7]);
    al_draw_scaled_bitmap(EXPLOSION_IMG , 130, 135, 52, 50, 0, 0, 80, 80, 0);

    al_set_target_bitmap(SPARK[0]);
    al_draw_scaled_bitmap(SPARK_IMG, 25, 25, 25, 25, 0, 0, 50 ,50, 0);
    al_set_target_bitmap(SPARK[1]);
    al_draw_scaled_bitmap(SPARK_IMG, 130, 43, 43, 35, 0, 0, 50 ,50, 0);
    al_set_target_bitmap(SPARK[2]);
    al_draw_scaled_bitmap(SPARK_IMG, 254, 31, 71, 65, 0, 0, 50 ,50, 0);
    al_set_target_bitmap(SPARK[3]);
    al_draw_scaled_bitmap(SPARK_IMG, 24, 135, 90, 95, 0, 0, 50 ,50, 0);

    al_set_target_bitmap(al_get_backbuffer(disp));

    for(int i=0;i<FX_N;i++){
        fx[i].used = false;
    }
}

void FX_add(bool spark, int x, int y, int scale){
    for(int i = 0; i < FX_N; i++){
        if(fx[i].used)
            continue;

        fx[i].x = x;
        fx[i].y = y;
        fx[i].frame = 0;
        fx[i].spark = spark;
        fx[i].scale = scale;
        fx[i].used = true;
        return;
    }
}



void FX_update(){
    for(int i = 0;i < FX_N; i++){
        if(!fx[i].used){
            continue;
        }
        fx[i].frame++;

        if((!fx[i].spark && (fx[i].frame == (EXPLOSION_FRAMES * 2))) || ( fx[i].spark && (fx[i].frame == (SPARKS_FRAMES * 2))))
            fx[i].used = false;

    }
}


void FX_draw(){
    for(int i = 0; i < FX_N; i++)
    {
        if(!fx[i].used)
            continue;

        int frame_display = fx[i].frame / 2;
        ALLEGRO_BITMAP* fxs =
            fx[i].spark
            ? SPARK[frame_display]
            : EXPLOSION[frame_display];

        int x = - al_get_bitmap_width(fxs) / 2;
        int y = - al_get_bitmap_height(fxs) / 2;
        al_build_transform(&FX_TRANSFORM, fx[i].x, fx[i].y, fx[i].scale / 2, fx[i].scale / 2, 0);
        al_use_transform(&FX_TRANSFORM);
        al_draw_bitmap(fxs, x, y, 0);
    }
}

void deinit_FX(){
  for(int i = 0;i < SPARKS_FRAMES;i++){
    al_destroy_bitmap(SPARK[i]);
  }
  for(int i = 0;i < EXPLOSION_FRAMES;i++){
    al_destroy_bitmap(EXPLOSION[i]);
  }
  al_destroy_bitmap(SPARK_IMG);
  al_destroy_bitmap(EXPLOSION_IMG);
}
