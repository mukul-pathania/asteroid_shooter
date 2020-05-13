#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

extern ALLEGRO_SAMPLE* blast_sound;
extern ALLEGRO_SAMPLE* trail_sound;
extern ALLEGRO_SAMPLE_ID trail_id;
extern ALLEGRO_SAMPLE* exp1_sound;
extern ALLEGRO_SAMPLE* exp2_sound;

void must_init(bool test, const char *description);

void audio_init();
void audio_deinit();

void play_bsound();
void play_tsound();
void play_exp1sound();
void play_exp2sound();







