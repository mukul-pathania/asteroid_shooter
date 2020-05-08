#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<math.h>
#include"asteroid.h"

ALLEGRO_TRANSFORM asteroid_transform;
int asteroid_count = 0;   //Asteroids that are active on screen.
ASTEROID asteroids[MAX_ASTEROID_COUNT];

/* Set everything up for using the array of asteroids.*/
void init_asteroids(){
    for(int i = 0; i < MAX_ASTEROID_COUNT; i++)
        asteroids[i].gone = true;
}


/*This function creates an asteroid outside the screen and gives the asteroid 
 *it's properties like speed, rotation, direction etc randomly 
 *and increments the asteroid_count variable.
 *This function is invisible to outside world, they can use it only through 
 the asteroid_trigger function declared below.*/
static void create_asteroid(ASTEROID* asteroid){
    int x = FLIP_COIN(1, -1);
    if(x == 1){
        asteroid->x = -20;
        asteroid->heading = RAND_DOUBLE_RANGE(DEG_TO_RAD(45), DEG_TO_RAD(135));
    }
    else{
        asteroid->x = SCREEN_WIDTH +20;
        asteroid->heading = RAND_DOUBLE_RANGE(DEG_TO_RAD(-45), DEG_TO_RAD(-135));
    }
    asteroid->y = RAND_DOUBLE_RANGE(0, SCREEN_HEIGHT);
    asteroid->speed = RAND_DOUBLE_RANGE(1,5);
    //asteroid->heading = RAND_DOUBLE_RANGE(DEG_TO_RAD(0), DEG_TO_RAD(359));
    asteroid->twist = 0;
    asteroid->rot_velocity = FLIP_COIN(0.5, -0.5);
    asteroid->rot_velocity *= RAND_DOUBLE_RANGE(0, DEG_TO_RAD(15));
    asteroid->scale = FLIP_COIN(1,2);
    asteroid->color = (rand() % 2) ? (al_map_rgb(255, 0 ,0)) : (al_map_rgb(0 ,255, 0));
    asteroid->circle.x = asteroid->x;
    asteroid->circle.y = asteroid->y;
    asteroid->circle.radius = 24*asteroid->scale;
    asteroid->life = 2 * asteroid->scale;
    asteroid->gone = false;
    asteroid_count++;
}

/*This function searches for an empty place in the asteroids array for the 
 *creation of an asteroid and passes it to the create asteroid function 
 *declared above.
 *This function also cannot be used directly but through asteroid_trigger 
 *function declared below.
 *It does nothing if all the elements the in asteroids are are in use.*/

static void create_new_asteroid(){
    for(int i = 0; i < MAX_ASTEROID_COUNT; i++){
        if(asteroids[i].gone){
            create_asteroid(&asteroids[i]);
            return;
        }
    }
}


/*This function updates all the asteroids in the asteroids array with their 
 *corresponding speed, rotation etc , i.e. make them move across the screen.*/
void update_asteroids(){
    float dx, dy;
    for(int i = 0; i < MAX_ASTEROID_COUNT; i++){
        if(asteroids[i].gone) //move to next asteroid if this asteroid is not active.
            continue;
        dx = sin(asteroids[i].heading) * asteroids[i].speed;
        dy = cos(asteroids[i].heading) * asteroids[i].speed;
        asteroids[i].circle.x = (asteroids[i].x += dx);
        asteroids[i].circle.y = (asteroids[i].y += dy);
    
        asteroids[i].twist += asteroids[i].rot_velocity;

        //check if the asteroid is on the screen, if it goes out of bounds then 
        //make the asteroid inactive and decrease the asteroid_count variable.
        if(asteroids[i].x < -50 || asteroids[i].x > SCREEN_WIDTH + 50 
                || asteroids[i].y < -50|| asteroids[i].y > SCREEN_HEIGHT + 50
                || asteroids[i].life == 0){
            
            asteroid_count--;
            asteroids[i].gone = true;
        }
    }
}

/*This funtion is passed an asteroid and it draws that asteroid.
 *Static because it is used through draw_all_asteroids functions declared below.*/
static void draw_asteroid(ASTEROID *a){
    al_build_transform(&asteroid_transform, a->x, a->y, a->scale, a->scale, a->twist);
    al_use_transform(&asteroid_transform);
	al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line(-25, 5, -25, -10, a->color, 2.0f);
	al_draw_line(-25, -10, -5, -10, a->color, 2.0f);
	al_draw_line(-5, -10, -10, -20, a->color, 2.0f);
	al_draw_line(-10, -20, 5, -20, a->color, 2.0f);
	al_draw_line(5, -20, 20, -10, a->color, 2.0f);
	al_draw_line(20, -10, 20, -5, a->color, 2.0f);
	al_draw_line(20, -5, 0, 0, a->color, 2.0f);
	al_draw_line(0, 0, 20, 10, a->color, 2.0f);
	al_draw_line(20, 10, 10, 20, a->color, 2.0f);
	al_draw_line(10, 20, 0, 15, a->color, 2.0f);
	al_draw_line(0, 15, -20, 20, a->color, 2.0f);
}
/*This function loops through the asteroids array and draws all the active asteroids to the screen*/
void draw_all_asteroids(){
    for(int i = 0; i < MAX_ASTEROID_COUNT; i++)
        if(!asteroids[i].gone)
            draw_asteroid(&asteroids[i]);
}

/*This function is responsible for the creation of new asteroids.
 *SPAWN_RATE is declared in the asteroid.h header.*/
void asteroid_trigger(){
    int i = rand() % SPAWN_RATE;
    //create a new asteroid only if i is 0 and number of asteroids currently on 
    //screen is less than max allowed asteroids on screen.
    if(i == 0 && asteroid_count < MAX_ASTEROID_COUNT)
        create_new_asteroid();
}
