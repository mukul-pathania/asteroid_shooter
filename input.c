#include "input.h"

bool key[ALLEGRO_KEY_MAX];

void init_input()
{
    memset(key, false, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch(event->type)
    {

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = true;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] = false;
            break;
    }
}


