#include "main.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "menusystem.h"
#include "HUD.h"

long long int points = 0, points_HUD = 0;
ALLEGRO_TRANSFORM HUD_TRANSFORM; 
ALLEGRO_FONT *hud_font;
ALLEGRO_COLOR health_color, lives_color;
int FPS, lives_count, health_count;
double newtime, oldtime, diff_time;
extern ALLEGRO_USTR *player1_name, *player2_name;

void add_points(int num){
    points += num;
}

long long int get_points(){
    return points;
}

void init_HUD(){
    hud_font = al_load_ttf_font("resources/SEASRN__.ttf", 19, 0);
    must_init(hud_font, "HUD font");
    newtime = oldtime = 0;
    lives_count = ship->lives;
    health_count = ship->health;
    health_color = al_map_rgb(0, 255, 0);//Green color when health is full.
    lives_color = al_map_rgb(0, 255, 0);
}

void update_HUD(){
    
    //We don't want to update the score immediately we want the score to keep rolling
    //as it will look better
    long long diff = 0;
    for(int i = 5; i > 0; i--){
        diff = 1 << i;
        if(points_HUD <= (points - diff))
            points_HUD += diff;
    }

    newtime = al_get_time();
    diff_time = newtime - oldtime;
    FPS = (1 / (diff_time * 1000)) * 1000;
    oldtime = newtime;
    if(ship->lives != lives_count){
        lives_count = ship->lives;
        //lives will show up in yellow or red according to this.
        lives_color = (lives_count <= 1) ? (al_map_rgb(255, 0, 0)) : al_map_rgb(255, 255, 0);
    }
    
    if(ship->health != health_count){
        health_count = ship->health;
        if(health_count > 66)
            health_color = al_map_rgb(0, 255, 0);
        else if(health_count > 33)
            health_color = al_map_rgb(255, 255, 0);
        else
            health_color = al_map_rgb(255, 0, 0);
    }

}


static void draw_gameover(){
    al_draw_filled_rectangle(270, SCREEN_HEIGHT / 4, 820, SCREEN_HEIGHT * 3 / 4 + 20, 
            al_map_rgba(0, 128, 128, 0.2));
    al_draw_multiline_textf(heading, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 4, SCREEN_WIDTH, 80, ALLEGRO_ALIGN_CENTER, "GAME OVER\n\n"
            "YOU SCORED\n%d POINTS.", points);
}

void draw_HUD(){

    al_build_transform(&HUD_TRANSFORM, 0, 0, 1, 1, 0);
    al_use_transform(&HUD_TRANSFORM);

    //If the pause menu is activated then stop displaying the HUD. 
    if(menu)
        return;

    //If the ship has no more lives left then display game over.
    if(ship->lives < 0){
        draw_gameover();
        return;
    }

    al_draw_textf(hud_font, al_map_rgb(255, 255, 255), SCREEN_WIDTH, 0, 
            ALLEGRO_ALIGN_RIGHT, "FPS:  %d", FPS);

    al_draw_ustr(hud_font, al_map_rgb(255, 255, 255), 0, 0,
            ALLEGRO_ALIGN_LEFT, player1_name);

    al_draw_textf(hud_font, lives_color, SCREEN_WIDTH, 20, 
            ALLEGRO_ALIGN_RIGHT, "Lives left:  %d", lives_count);

    al_draw_textf(hud_font, health_color, 0, 20, 
            ALLEGRO_ALIGN_LEFT, "Health:  %d", health_count);

    al_draw_textf(hud_font, al_map_rgb(255, 255, 255), 0, 40, 
            ALLEGRO_ALIGN_LEFT, "Points:  %lld", points_HUD);

}
