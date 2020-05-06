objects = main.o asteroid.o spaceship.o input.o blast.o sounds.o
allegro = `pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags` 

main: $(objects)
	gcc $(objects) -o main $(allegro) -lm

main.o: asteroid.h spaceship.h input.h blast.h
asteroid.o: asteroid.h
spaceship.o: asteroid.h spaceship.h input.h
input.o: input.h
blast.o: blast.h spaceship.h input.h asteroid.h
sounds.o: sounds.h input.h

.PHONY: clean
clean:
	rm main $(objects)
