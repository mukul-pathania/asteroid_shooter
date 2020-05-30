#include "sounds.h"
//#include "spaceship.h"
#include "input.h"
//#include "blast.h"

ALLEGRO_SAMPLE* blast_sound;
ALLEGRO_SAMPLE* trail_sound;
ALLEGRO_SAMPLE_ID trail_id;
ALLEGRO_SAMPLE* exp1_sound;
ALLEGRO_SAMPLE* exp2_sound;
ALLEGRO_AUDIO_STREAM *menu_music;
ALLEGRO_AUDIO_STREAM *background_music;

void must_init(bool test, const char *description);

void audio_init(){
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), " audio acodecs");
    must_init(al_reserve_samples(128), "reserve samples");

    blast_sound = al_load_sample("resources/shot.flac");
    must_init(blast_sound, "blast sound");
    trail_sound = al_load_sample("resources/rocket_thrusters.wav");
    must_init(trail_sound, "trail sound");
    exp1_sound = al_load_sample("resources/explode1.flac");
    must_init(exp1_sound, "explode sound");
    exp2_sound = al_load_sample("resources/explode3.wav");
    must_init(exp2_sound, "explode sound");
}

void destroy_audio(){   
    al_destroy_sample(blast_sound);
    al_destroy_sample(trail_sound);
    al_destroy_sample(exp1_sound);
    al_destroy_sample(exp2_sound);
    al_destroy_audio_stream(menu_music);
    al_destroy_audio_stream(background_music);
}  

void play_bsound(){
    al_play_sample(blast_sound, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_tsound(){
    al_play_sample(trail_sound, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, &trail_id);
} 

void play_exp1sound(){
    al_play_sample(exp1_sound, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_exp2sound(){
    al_play_sample(exp2_sound, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
} 

void play_menu_music(){
    menu_music = al_load_audio_stream("resources/Background_music2.opus", 2, 2048);
    must_init(menu_music , "Menu music");
    al_set_audio_stream_playmode(menu_music, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(menu_music, al_get_default_mixer());
}

void stop_menu_music(){
    al_set_audio_stream_playing(menu_music, false);
}

void play_background_music(){
    background_music = al_load_audio_stream("resources/Background_music1.opus", 2, 2048);
    must_init(background_music , "background music");
    al_set_audio_stream_playmode(background_music, ALLEGRO_PLAYMODE_LOOP);
    al_attach_audio_stream_to_mixer(background_music, al_get_default_mixer());
}

void stop_background_music(){
    al_set_audio_stream_playing(background_music, false);
}
