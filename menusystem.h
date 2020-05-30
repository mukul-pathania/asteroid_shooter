#ifndef FILE_HUD_SEEN
#define FILE_HUD_SEEN 1

void init_menusystem();
void destroy_menusystem();
void welcome_screen();

typedef struct{
    float x1, y1, x2, y2;
    ALLEGRO_FONT *font;
    char *text;
    void (*handler)();
}MENU;

extern MENU main_menu[5];

#endif //menusystem.h
