#ifndef FILE_HUD_SEEN
#define FILE_HUD_SEEN 1

extern ALLEGRO_FONT *heading;
void init_HUD();
void destroy_HUD();
void draw_welcome();
void welcome_screen();

typedef struct{
    float x1, y1, x2, y2;
    ALLEGRO_FONT *font;
    char *text;
    void (*handler)();
}MENU;

extern MENU menu[5];

#endif //HUD.h
