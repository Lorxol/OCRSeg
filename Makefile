all: main

main: main.c seg.c seg.h
	gcc -Wall -Wextra -Werror -std=c99 -O1 -o main *.c -lm  `sdl2-config --cflags --libs`

clean:
	rm -f main
