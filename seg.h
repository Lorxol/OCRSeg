#ifndef SEG_H
#define SEG_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"


//Main function
int seg(SDL_Surface *img);

Uint32 getpixel(SDL_Surface* surface, int x, int y);
//Change color of a pixel in surface
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

//Just to save some space: initialize tcm to 0
void cleantcm();
void printtcm();
//Because I suck at coding
void transpo();

//Obvious
int max(int a, int b, int c);
int min(int a, int b, int c);

//Color->Greyscale->B&W + line detection
void lineSight(SDL_Surface *img);
//Recursive character detection
void rowSight(SDL_Surface *img, unsigned long x, unsigned long y, int xtcm, int ytcm, unsigned int nbchar);

#endif
