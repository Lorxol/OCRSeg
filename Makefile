all: main

main: main.c seg.c seg.h
	gcc -Wall -Wextra -Werror -std=c99 -O1 `sdl2-config --cflags --libs` -o main -c *.c

clean:
	rm -f *.o
