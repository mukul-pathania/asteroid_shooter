#include "sounds.h"
//#include "spaceship.h"
#include "input.h"
//#include "blast.h"

ALLEGRO_SAMPLE* blast_sound;
ALLEGRO_SAMPLE* trail_sound;

void must_init(bool test, const char *description);

void audio_init(){
     must_init(al_install_audio(), "audio");
     must_init(al_init_acodec_addon(), " audio acodecs");
     must_init(al_reserve_samples(20), "reserve samples");
     
     blast_sound = al_load_sample("resources/shot.flac");
     must_init(blast_sound, "blast sound");
     trail_sound = al_load_sample("resources/jet.wav");
     must_init(trail_sound, "trail sound");     
}

void audio_deinit(){   
     al_destroy_sample(blast_sound);
     al_destroy_sample(trail_sound);
}  

void play_bsound(){
     al_play_sample(blast_sound, 3,0,1,ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_tsound(){
     al_play_sample(trail_sound, 0.5, 0,2, ALLEGRO_PLAYMODE_ONCE, NULL);
}    
