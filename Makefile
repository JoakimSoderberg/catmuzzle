
all:
	gcc -Wall -std=c99 -pedantic -O3 -o catmuzzle -Isrc src/*.c -lm -fopenmp

debug:
	gcc -Wall -std=c99 -pedantic -g -o catmuzzle -Isrc src/*.c -lm -fopenmp

clean:
	rm -f catmuzzle
