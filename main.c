#include "blast_effect.h"
#include "input.h"
#include "blast.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "sounds.h"
#include "bgspace.h"
#include <time.h>
#include "planets.h"

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
ALLEGRO_DISPLAY* disp;

int main()
{
    
    srandom(time(0));
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(),"mouse");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_image_addon(), "image-addon");
    audio_init();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);


    init_asteroids(); //initialise asteroids for use.
    init_input();  //To handle keyboard events
    init_ship();   //initialize ship
    init_blasts(); //initialise blasts
    init_star();
    effect_init();
    init_planet();
    
    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                star_update();
                check_and_handle_collisions();//check for collision between and blasts and asteroids and handle them if any.
                asteroid_trigger(); //create new asteroids.
                update_asteroids(); //update all the asteroids on screen.
                ship_update(ship); //update ship
                blast_trigger(); //create blasts
                update_blasts();  //update the blasts on the screen.
                effect_update();
                trigger_comet();
                update_comet();

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                redraw = true;


                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] = false;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        keyboard_update(&event);

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_translate_transform(&transform, 0, 0);
            al_use_transform(&transform);
            draw_comets();
            draw_planet();
            star_create();
            effect_draw();
            al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Asteroids: %3d", asteroid_count);
            draw_all_asteroids();
            draw_ship(ship); // draws spaceship
            draw_all_blasts(); //draws all the blasts
            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    deinit_asteroids();
    audio_deinit();
    deinit_ship();
    destroy_planet();
    return 0;
}
