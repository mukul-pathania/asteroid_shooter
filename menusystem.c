/*This file contains all the things that are required for drawing the
 *menu on the screen. */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "menusystem.h"
#include "bgspace.h"
#include "input.h"
#include "sounds.h"
#include "asteroid.h"
#include "main.h"

ALLEGRO_FONT *heading, *options, *highlighted_option;
ALLEGRO_TRANSFORM menusystem_transform;
static void init_main_menu();
static void draw_menu();
int current_option = 0;
bool done = false;//keep it here start_game_option_handler uses it.

void init_menusystem(){
    must_init(al_init_font_addon(), "Font addon");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_install_mouse(), "Mouse");

    heading = al_load_ttf_font("resources/SEASRN__.ttf", 72, 0);
    must_init(heading, "Heading Font");
    options = al_load_ttf_font("resources/SEASRN__.ttf", 32, 0);
    must_init(options, "Font for options");
    highlighted_option = al_load_ttf_font("resources/SEASRN__.ttf", 50, 0);
    must_init(highlighted_option, "Font for chosen option");


    init_main_menu();
}


static void start_game_option_handler(){
    done = true;
}
/*Couldn't think of a name.*/
static void options_option_handler(){
    ;//do nothing for now.
}
static void controls_option_handler(){
    ;//do nothing for now
}
static void credits_option_handler(){
    ;//do nothing for now
}
static void exit_option_handler(){
    destroy_main();
    exit(0);
}

void destroy_menusystem(){
    al_destroy_font(heading);
    al_destroy_font(options);
    al_destroy_font(highlighted_option);
}


MENU main_menu[5];
static void init_main_menu(){
    for(int i = 0, y = 250; i < 5; i++, y += 70){
        main_menu[i].x1 = 370;
        main_menu[i].x2 = 710;
        main_menu[i].y1 = y;
        main_menu[i].y2 = y + 70;
        main_menu[i].font = options;
    }
    main_menu[0].text = "START GAME";
    main_menu[0].handler = start_game_option_handler;
    main_menu[1].text = "OPTIONS";
    main_menu[1].handler = options_option_handler;
    main_menu[2].text = "CONTROLS";
    main_menu[2].handler = controls_option_handler;
    main_menu[3].text = "CREDITS";
    main_menu[3].handler = credits_option_handler;
    main_menu[4].text = "EXIT";
    main_menu[4].handler = exit_option_handler;
}




static void draw_menu(){
    for(int i = 0; i < 5; i++){
        if(i == current_option){
            al_draw_filled_rectangle(main_menu[i].x1, main_menu[i].y1, main_menu[i].x2, main_menu[i].y2, al_map_rgba(255, 255, 255, 0.2));
            al_draw_text(highlighted_option, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2,
                    main_menu[i].y1, ALLEGRO_ALIGN_CENTER, main_menu[i].text);
            continue;
        }
        al_draw_text(main_menu[i].font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2,
                main_menu[i].y1, ALLEGRO_ALIGN_CENTER, main_menu[i].text);
    }
}

static void draw_welcome(){
    al_build_transform(&menusystem_transform, 0, 0, 1, 1, 0);
    al_use_transform(&menusystem_transform);
    al_draw_filled_rectangle(120, 5, 950, 180, al_map_rgba(0, 128, 128, 0.2));
    al_draw_multiline_text(heading, al_map_rgb(255, 255, 0), SCREEN_WIDTH / 2,
            0, SCREEN_WIDTH, 80, ALLEGRO_ALIGN_CENTER, "Welcome to Asteroid-Shooter");

    draw_menu();
}

static void handle_mouse_hover_and_click(ALLEGRO_EVENT *event){
    int x = 0, y = 0;
    bool clicked = false;
    switch(event->type){

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if(event->mouse.button & 1)
                clicked = true;
            //no break is added here to use fall through
        case ALLEGRO_EVENT_MOUSE_AXES:
            x = event->mouse.x;
            y = event->mouse.y;
            break;
    }

    if(x || y)
        for(int i = 0 ; i < 5; i++)
            if(x > main_menu[i].x1 && x < main_menu[i].x2 && y > main_menu[i].y1 &&  y < main_menu[i].y2){
                current_option = i;
                if(clicked)
                    main_menu[current_option].handler();
            }

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
                asteroid_trigger();
                update_asteroids();

                if(key[ALLEGRO_KEY_DOWN])
                    current_option++;

                if(key[ALLEGRO_KEY_UP])
                    current_option--;

                if(current_option > 4)
                    current_option = 0;

                if(current_option < 0)
                    current_option = 4;

                if(key[ALLEGRO_KEY_ESCAPE]){
                    destroy_main();
                    exit(0);
                }

                if(key[ALLEGRO_KEY_ENTER])
                    main_menu[current_option].handler();
                break;


            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                destroy_main();
                exit(0);

        }
        handle_mouse_hover_and_click(&event);
        keyboard_update(&event);
        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_bgspace();
            draw_all_asteroids();
            draw_welcome();
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    stop_menu_music();
}
