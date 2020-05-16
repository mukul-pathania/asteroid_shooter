#include <math.h>
#include "bgspace.h"
#include<allegro5/allegro_primitives.h>

void must_init(bool, const char *);
STAR stars[STAR_COUNT];
//ALLEGRO_TRANSFORM comet_transform;
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

ALLEGRO_BITMAP *PLANET, *COMET, *planet, *comet;
COMETS comets[MAX_COMET_COUNT];
extern ALLEGRO_DISPLAY *disp;
int i,comet_count=0;
void init_planet(){

    planet = al_load_bitmap("resources/planet.png");
    must_init(planet, "Planet image");
    comet = al_load_bitmap("resources/comet.png");
    must_init(comet, "Comet image");

    PLANET = al_create_bitmap(200,150);
    al_set_target_bitmap(PLANET);
    al_draw_scaled_bitmap(planet, 0, 0, 900, 434, 0, 0, 200, 150, 0);
    al_set_target_bitmap(al_get_backbuffer(disp));
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
void draw_planet(){
    al_draw_bitmap(PLANET, 80, 70, 0);
}

void destroy_planet(){
    al_destroy_bitmap(PLANET);
    al_destroy_bitmap(COMET);
    al_destroy_bitmap(comet);
    al_destroy_bitmap(planet);
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
 
    /*al_build_transform(&comet_transform, c->circle.x, c->circle.y, 1, 1, 0);
    al_use_transform(&comet_transform);
   al_draw_circle(0, 0, c->circle.radius, al_map_rgb(255, 0, 0), 3.0f);*/
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


