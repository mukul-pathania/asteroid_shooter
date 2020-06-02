#ifndef FILE_HUD_SEEN
#define FILE_HUD_SEEN 1


typedef struct{
    float x1, y1, x2, y2;
    ALLEGRO_FONT *font;
    char *text;
    void (*handler)();
}MENU;

extern MENU main_menu[4];
extern MENU pause_menu[2];
void init_menusystem();
void destroy_menusystem();
void welcome_screen();
void draw_pause_menu();
void handle_mouse_hover_and_click(ALLEGRO_EVENT* , MENU* , int, int*);

#endif //menusystem.h
