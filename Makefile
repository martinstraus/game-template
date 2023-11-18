build:
	gcc -g -o game game.c -lGL -lGLU -lglut -lGLEW -lm

clean:
	rm abstract
