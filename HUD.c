/*This file contains all the thibgs taht are required for drawing the
 *menu on the screen. */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"
#include "HUD.h"
#include "bgspace.h"
#include "input.h"
#include "sounds.h"

extern ALLEGRO_DISPLAY* disp;
void must_init(bool, const char*);
ALLEGRO_FONT *heading, *options;

void init_HUD(){
    must_init(al_init_font_addon(), "Font addon");
    must_init(al_init_ttf_addon(), "ttf addon");

    heading = al_load_ttf_font("resources/SEASRN__.ttf", 72, 0);
    must_init(heading, "Heading Font");
    options = al_load_ttf_font("resources/SEASRN__.ttf", 36, 0);
    must_init(options, "Font for options");
}
void destroy_HUD(){
    al_destroy_font(heading);
    al_destroy_font(options);
}

void draw_welcome(){
    al_draw_filled_rectangle(150, 50, 930, 240, al_map_rgba(0, 128, 128, 0.2));
    al_draw_multiline_text(heading, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
            50, SCREEN_WIDTH, 80, ALLEGRO_ALIGN_CENTER, "Welcome to Asteroid-Shooter");

    al_draw_text(options, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            250, ALLEGRO_ALIGN_CENTER, "START GAME");

    al_draw_text(options, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            320, ALLEGRO_ALIGN_CENTER, "OPTIONS");
    
    al_draw_text(options, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            390, ALLEGRO_ALIGN_CENTER, "CONTROLS");
    
    al_draw_text(options, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            460, ALLEGRO_ALIGN_CENTER, "CREDITS");
    
    al_draw_text(options, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
            530, ALLEGRO_ALIGN_CENTER, "EXIT");
}

void welcome_screen(){
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer welcome screen");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue welcome screen");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    
    bool redraw = true;
    bool done = false;
    ALLEGRO_EVENT event;
    play_menu_music();
    
    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                update_bgspace();
                trigger_bgspace();
                if(key[ALLEGRO_KEY_ESCAPE])
                    exit(0);
                if(key[ALLEGRO_KEY_ENTER])
                    done = true;
                break;


            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit(0);

        }
        keyboard_update(&event);
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_bgspace();
            draw_welcome();
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    stop_menu_music();
}
