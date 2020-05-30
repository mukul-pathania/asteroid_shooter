objects = main.o asteroid.o spaceship.o input.o blast.o sounds.o collision.o bgspace.o FX.o menusystem.o
allegro = `pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5  allegro_ttf-5 --libs --cflags` 

main: $(objects)
	gcc $(objects) -o main $(allegro) -lm

main.o: main.h asteroid.h spaceship.h input.h blast.h FX.h sounds.h bgspace.h menusystem.h
asteroid.o: asteroid.h  main.h collision.h
spaceship.o: main.h spaceship.h input.h collision.h sounds.h
input.o: input.h
blast.o: blast.h spaceship.h input.h main.h asteroid.h
sounds.o: sounds.h input.h
bgspace.o: bgspace.h main.h asteroid.h
collision.o: collision.h asteroid.h blast.h FX.h sounds.h spaceship.h 
FX.o: FX.h
menusystem.o: menusystem.h main.h bgspace.h input.h sounds.h 

.PHONY: clean
clean:
	rm main $(objects)
