#define MAX_SPACESHIP_SPEED 20
#define SPACESHIP_BRAKE_GRADIENT 1.2
#define SPACESHIP_ACC_GRADIENT 1.2
#define MAX_TURN_RATE DEG_TO_RAD(6)

extern ALLEGRO_BITMAP *SPRITESHEET, *SHIP, *TRAIL;

typedef struct{
    float x, y, speed, heading, scale;
    bool is_drifting;
}SPACESHIP;

extern SPACESHIP *ship;
extern ALLEGRO_TRANSFORM ship_transform;
void init_ship();

void draw_ship(SPACESHIP *ship);
void ship_update(SPACESHIP *ship);
