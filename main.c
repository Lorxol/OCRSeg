#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL2/SDL.h"
#include "seg.h"
#include "neural_network.h"
#include "my_math_lib.h"

void hardcode(Network *n)
{
	n->layers[0].weights.mat[0] = -10;
	n->layers[0].weights.mat[1] = -10;
	n->layers[0].weights.mat[2] = 10;
	n->layers[0].weights.mat[3] = 10;
	n->layers[0].biais.vec[0] = 5;
	n->layers[0].biais.vec[1] = -15;
	n->layers[1].weights.mat[0] = -10;
	n->layers[1].weights.mat[1] = -10;
	n->layers[1].biais.vec[0] = 5;
}

int main(int argc, char **argv)
{
	//Declaring and initializing useful variables
	char path[50] = "";
        SDL_Event ev;

        if(argc != 2)
        {
          printf("Error invalid number of arguments.");
          return EXIT_FAILURE;
        }

	if(strcmp(argv[1],"xor") == 0)
	{
		printf("Everything work, exept back propagation.\n");
	printf("We can hard code a neural network and he computes well.\n");
		int arr[3] = {2, 2, 1};
		Network n = new_null_network(2, arr, 1);
		hardcode(&n);
		Vector v = new_null_vec(2);
		printf("0 xor 0 = %lf\n", forward(n, v).vec[0]);
		vec_new_val(&v, 1, 1);
		printf("0 xor 1 = %lf\n", forward(n, v).vec[0]);
		vec_new_val(&v, 1, 0);
		vec_new_val(&v, 0, 1);
		printf("1 xor 0 = %lf\n", forward(n, v).vec[0]);
		vec_new_val(&v, 1, 1);
		printf("1 xor 1 = %lf\n", forward(n, v).vec[0]);



				
		return EXIT_SUCCESS;
	}

	strcat(path, argv[1]);
	strcat(path,".bmp");

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

	//A little bit of event management
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


