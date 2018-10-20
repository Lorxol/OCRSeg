#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "seg.h"

int main(int argc, char **argv)
{
	//Declaring and initializing useful variables
	char path[50] = "img_files/";
	strcat(path, argv[1]);
	strcat(path,".bmp");
        SDL_Event ev;

        if(argc != 2)
        {
          printf("Error invalid number of arguments.");
          return EXIT_FAILURE;
        }

    	//Initializing SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
	  fprintf(stderr, "Init SDL failure:%s\n", SDL_GetError());
	  return EXIT_FAILURE;
	}

	//Loading first bmp picture
	SDL_Surface* img = SDL_LoadBMP(path);
	if (img == NULL)
	{
          fprintf(stderr, "Get image bmp failure:%s\n", SDL_GetError());
          return EXIT_FAILURE;
	}

	//Dimensions of the window
	int wd_w=img->w, wd_h=img->h;



	//Creating window
	SDL_Window*  wd = SDL_CreateWindow("SDL_temp", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, wd_w, wd_h, SDL_WINDOW_SHOWN);

	if (!wd)
	{
	  fprintf(stderr, "Init SDL Window failure:%s\n", SDL_GetError());
	  return EXIT_FAILURE;
	}
	
	
	

    	//Processing line segmentation and B&W conversion
	seg(img);

	//Getting ready to blit img
	SDL_Rect img_dest = {0, 0, 0, 0};
	SDL_Surface* wdsfc = SDL_GetWindowSurface(wd);
	//Blitting img on wd
	SDL_BlitSurface(img, NULL, wdsfc, &img_dest);
	
	//Moving img from buffer to screen
	SDL_UpdateWindowSurface(wd);

        while(SDL_WaitEvent(&ev) >= 0)
          {
            switch(ev.type)
             {
               case SDL_QUIT:
                 return 0;
               break;
             }
          }


	//Exiting properly SDL
	SDL_FreeSurface(img);
	SDL_FreeSurface(wdsfc);
	SDL_DestroyWindow(wd);
	SDL_Quit();
	return EXIT_SUCCESS;
}


