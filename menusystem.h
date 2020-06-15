#ifndef FILE_MENUSYSTEM_SEEN
#define FILE_MENUSYSTEM_SEEN 1

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

typedef struct{
    float x1, y1, x2, y2;
    ALLEGRO_FONT *font;
    char *text;
    void (*handler)();
}MENU;

//For sharing fonts to other files
extern ALLEGRO_FONT *heading, *options, *highlighted_option;
extern ALLEGRO_FONT *medium_scale, *small_scale;

extern MENU main_menu[4];
extern MENU pause_menu[2];
extern ALLEGRO_USTR *player1_name, *player2_name;
void init_menusystem();
void destroy_menusystem();
void welcome_screen();
void draw_pause_menu();
void handle_mouse_hover_and_click(ALLEGRO_EVENT* , MENU* , int, int*);

#endif //menusystem.h
