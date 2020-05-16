extern ALLEGRO_BITMAP *PLANET , *PLANETS[5];
extern bool planet_gone;
extern ALLEGRO_DISPLAY* disp;
extern int x0,y0,x1,y1,x2,y2,x3,y3,x4,y4;

void init_planets();
void draw_planets();
void update_planets();
