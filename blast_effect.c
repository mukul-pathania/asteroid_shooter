#include <stdlib.h>
#include <stdio.h>
#include "collision.h"
#include "asteroid.h"
#include "blast_effect.h"
#include "blast.h"


EFFECT effect[EFFECT_N];
ALLEGRO_BITMAP *SPARK[SPARKS_FRAMES], *EXPLOSION[EXPLOSION_FRAMES], *EXPLOSION_IMG, *SPARK_IMG;
void must_init(bool, const char *);

void effect_init(){

    EXPLOSION_IMG = al_load_bitmap("resources/explosion.png");
    SPARK_IMG = al_load_bitmap("resources/sparks.png");

    if(!EXPLOSION_IMG){
        fprintf(stderr, "Couldn't load Explosions");
        exit(1);
    }
    if(!SPARK_IMG){
        fprintf(stderr, "Couldn't load Sparks");
        exit(1);
    }
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

    for(int i=0;i<EFFECT_N;i++){
        effect[i].used = false;
    }
}

void effect_add(bool spark, int x, int y){
    for(int i = 0; i < EFFECT_N; i++){
        if(effect[i].used)
            continue;

        effect[i].x = x;
        effect[i].y = y;
        effect[i].frame = 0;
        effect[i].spark = spark;
        effect[i].used = true;
        return;
    }
}



void effect_update(){
    for(int i = 0;i < EFFECT_N; i++){
        if(!effect[i].used){
            continue;
        }
        effect[i].frame++;

        if((!effect[i].spark && (effect[i].frame == (EXPLOSION_FRAMES * 2))) || ( effect[i].spark && (effect[i].frame == (SPARKS_FRAMES * 2))))
            effect[i].used = false;

    }
}


void effect_draw(){
    for(int i = 0; i < EFFECT_N; i++)
    {
        if(!effect[i].used)
            continue;

        int frame_display = effect[i].frame / 2;
        ALLEGRO_BITMAP* effects =
            effect[i].spark
            ? SPARK[frame_display]
            : EXPLOSION[frame_display];

        int x = effect[i].x - (al_get_bitmap_width(effects) / 2);
        int y = effect[i].y - (al_get_bitmap_height(effects) / 2);
        al_draw_bitmap(effects, x, y, 0);
    }
}
