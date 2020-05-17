#include <math.h>
#include "bgspace.h"
#include <stdio.h>
#include <stdlib.h>
#include<allegro5/allegro_primitives.h>

void must_init(bool, const char *);
STAR stars[STAR_COUNT];
ALLEGRO_BITMAP *PLANET , *PLANETS[5];
ALLEGRO_DISPLAY* disp;
float x1,y_1,x2,y2,x3,y3,x4,y4;

void must_init(bool test, const char *description);

void init_planets(){
    PLANET = al_load_bitmap("resources/planet.png");
    if(!PLANET){
        fprintf(stderr, "Couldn't load Planet");
        exit(1);
    }
    PLANETS[0] = al_create_bitmap(180, 135);
    must_init(PLANETS[0], "PLANET[]");
    PLANETS[1] = al_create_bitmap(130, 135);
    must_init(PLANETS[1], "PLANET[]");
    PLANETS[2] = al_create_bitmap(120, 120);
    must_init(PLANETS[2], "PLANET[]");
    PLANETS[3] = al_create_bitmap(130, 130);
    must_init(PLANETS[3], "PLANET[]");
    PLANETS[4] = al_create_bitmap(90, 90);
    must_init(PLANETS[4], "PLANET[]");

    al_set_target_bitmap(PLANETS[0]);
    al_draw_scaled_bitmap(PLANET, 350, 65, 135, 135, 0, 0, 135, 135, 0);
    al_set_target_bitmap(PLANETS[1]);
    al_draw_scaled_bitmap(PLANET, 500, 70, 130, 135, 0, 0, 130, 135, 0);
    al_set_target_bitmap(PLANETS[2]);
    al_draw_scaled_bitmap(PLANET, 365, 230, 110, 110, 0, 0, 120, 120, 0);
    al_set_target_bitmap(PLANETS[3]);
    al_draw_scaled_bitmap(PLANET, 495, 210, 140, 140, 0, 0, 130, 130, 0);
    al_set_target_bitmap(PLANETS[4]);
    al_draw_scaled_bitmap(PLANET, 530, 377, 90, 90, 0, 0, 90, 90, 0);

    al_set_target_bitmap(al_get_backbuffer(disp));
    x1 = 100, x2 = 500; x3 = 800, x4 = 100;
    y_1 = 200 ,y2 = 400, y3 = 0, y4 = -100;


}
void draw_planets(){

    al_draw_bitmap(PLANETS[0], x1, y_1, 0);
    al_draw_bitmap(PLANETS[3], x2, y2, 0);
    al_draw_bitmap(PLANETS[4], x3, y3, 0);

    if(y_1 >= SCREEN_HEIGHT-135){
        al_draw_bitmap(PLANETS[0], x1, y_1, 0);
        al_draw_bitmap(PLANETS[0], x1, y_1-SCREEN_HEIGHT, 0);
    }
    if(y2 >= SCREEN_HEIGHT-140){
        al_draw_bitmap(PLANETS[3], x2, y2, 0);
        al_draw_bitmap(PLANETS[3], x2, y2-SCREEN_HEIGHT, 0);
    }
    if(y3 >= SCREEN_HEIGHT-90){
        al_draw_bitmap(PLANETS[4], x3, y3, 0);
        al_draw_bitmap(PLANETS[4], x3, y3-SCREEN_HEIGHT, 0);
    }

}


void update_planets(){

    if(y_1 >= SCREEN_HEIGHT){
        y_1 -= SCREEN_HEIGHT;
    }
    if(y2 >= SCREEN_HEIGHT){
        y2 -= SCREEN_HEIGHT;
    }
    if(y3 >= SCREEN_HEIGHT){
        y3 -= SCREEN_HEIGHT;
    }
    y_1+=1.8;
    y2+=1;
    y3+=2.5;

}

void init_star(){
    int x = 1;

    for(int i=0; i < STAR_COUNT ; i++, x += 2){
        stars[i].x = x;
        stars[i].y = rand() % SCREEN_HEIGHT ;
        stars[i].speed = RAND_DOUBLE_RANGE(0.1, 1);
    }
}

void star_update(){

    for(int i=0; i < STAR_COUNT; i++){

        stars[i].y += stars[i].speed;
        if (stars[i].y > SCREEN_HEIGHT){
            stars[i].y = 0;
        }
    }
}

void star_create(){
    float l;

    for(int i=0; i < STAR_COUNT; i++){
        l = stars[i].speed;
        al_draw_pixel(stars[i].x , stars[i].y, al_map_rgb(0, l * 255, l * 255));
    }
}

ALLEGRO_BITMAP *COMET, *comet;
COMETS comets[MAX_COMET_COUNT];
extern ALLEGRO_DISPLAY *disp;
int i,comet_count=0;
void init_planet(){

    comet = al_load_bitmap("resources/comet.png");
    must_init(comet, "Comet image");

    for(i=0;i<MAX_COMET_COUNT;i++){
        comets[i].gone = true;
    }
    COMET = al_create_bitmap(20,20);
    al_set_target_bitmap(COMET);
    al_draw_scaled_bitmap(comet, 0, 0,508,508, 0, 0,20,20,0);
    al_set_target_bitmap(al_get_backbuffer(disp));
}


static void create_comet(COMETS *com){


    com->x =rand() % SCREEN_WIDTH;
    com->y = 0;//rand() % SCREEN_HEIGHT;

    com->speed = 2;
    com->scale = 2;
    com->circle.x = com->x;
    com->circle.y = com->y;
    com->circle.radius = 10;
    com->gone = false;
    comet_count++;

}


void destroy_planet(){
    al_destroy_bitmap(COMET);
    al_destroy_bitmap(comet);
}

void update_comet(){

    for(i=0; i<MAX_COMET_COUNT; i++){
        float dx,dy;
        if(comets[i].gone)
            continue;
        dx = dy = comets[i].speed;
        //comets[i].x -= comets[i].speed;
        //comets[i].y += comets[i].speed;
        comets[i].circle.x = (comets[i].x -= dx);
        comets[i].circle.y = (comets[i].y += dy); 

        if (comets[i].x > SCREEN_WIDTH || comets[i].x < 0 || comets[i].y >
                SCREEN_HEIGHT || comets[i].y < 0 ){
            comet_count--;
            comets[i].gone = true;
        }
    }
}

static void draw_comet(COMETS *c){
    al_draw_bitmap(COMET, c->x,c->y, 0);
}

void draw_comets(){
    for(i=0;i<MAX_COMET_COUNT;i++){
        if(!comets[i].gone)
            draw_comet(&comets[i]);

    }
}

void create_new_comet(){
    for(i=0;i<MAX_COMET_COUNT;i++){
        if(comets[i].gone){
            create_comet(&comets[i]);
            return;
        }
    }
}

void trigger_comet(){
    if (comet_count < MAX_COMET_COUNT )
        create_new_comet();
}
