/*This file contains all the thibgs taht are required for drawing the
 *menu on the screen. */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include "asteroid.h"
#include "HUD.h"

void must_init(bool, const char*);
ALLEGRO_FONT *heading;

void init_HUD(){
    must_init(al_init_font_addon(), "Font addon");
    must_init(al_init_ttf_addon(), "ttf addon");

    heading = al_load_ttf_font("resources/Pacifico.ttf", 72, 0);
    must_init(heading, "Heading Font");
}
void destroy_HUD(){
    al_destroy_font(heading);
}

void draw_welcome(){
    al_draw_text(heading, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            50, ALLEGRO_ALIGN_CENTER, "Welcome to Asteroid-Shooter");
}
