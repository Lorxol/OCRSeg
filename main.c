#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

//Declaring global variables
int maxHeight = 0; //Maximal height of a letter in pixels

//Gets RGB components of a pixel in surface
Uint32 getpixel(SDL_Surface* surface, int x, int y);
//Change color of a pixel in surface
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

//Obvious
int max(int a, int b, int c);
int min(int a, int b, int c);

//Color->Greyscale->B&W + line detection
void lineSight(SDL_Surface *img, int* nbLines);
void rowSight(SDL_Surface *img, unsigned long x, unsigned long y);

int main()
{
	//Declaring useful variables
	char path[50] = "img_files/darker.bmp";
    	int nbLines = 0;
	maxHeight = 0;

	//Initializing SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
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
	SDL_Window*  wd = SDL_CreateWindow("SDL_temp", SDL_WINDOWPOS_UNDEFINED,  SDL_WINDOWPOS_UNDEFINED, wd_w, wd_h, SDL_WINDOW_SHOWN);

	if (!wd)
	{
		fprintf(stderr, "Init SDL Window failure:%s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	
	

	SDL_LockSurface(img);
    //Processing line segmentation and B&W conversion
    lineSight(img, &nbLines);

	SDL_UnlockSurface(img);

	//Getting ready to blit img
	SDL_Rect img_dest = {0, 0, 0, 0};
	SDL_Surface* wdsfc = SDL_GetWindowSurface(wd);
	//Blitting img on wd
	SDL_BlitSurface(img, NULL, wdsfc, &img_dest);
	
	//Moving img from buffer to screen
	SDL_UpdateWindowSurface(wd);



	SDL_Delay(10000);


	//Exiting properly SDL
	SDL_FreeSurface(img);
	SDL_FreeSurface(wdsfc);
	SDL_DestroyWindow(wd);
	SDL_Quit();
	return EXIT_SUCCESS;
}

Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p =(Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp)
	{
		case 1:
			return *p;
			break;
		case 2:
			return *(Uint16 *)p;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
			break;
		case 4:
			return *(Uint32 *)p;
			break;
		default:
			return 0;
	}
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp)
	{
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}
			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}	

int max(int a, int b, int c)
{
	int max = a;

	if(b > max)
		max = b;

	if(c > max)
		max = c;

	return max;
}

int min(int a, int b, int c)
{
	int min = a;

	if(b < min)
		min = b;

	if(c < min)
		min = c;

	return min;
}

void lineSight(SDL_Surface *img, int* nbLines)
{

	Uint8 rpix=0, gpix=0, bpix=0; //Temp variables for storing pixel color
	unsigned long bwthreshold = 0; //Defines which pixel will be white or black
    Uint8 isptl = 0; //Is parsing text line (boolean)
    Uint8 *tempLine = NULL;
    tempLine = malloc(img->w * sizeof(Uint8));
    int tempMax = 0;
    unsigned long nbPix = img->w * img->h;

    for(int i=0;i<img->h;i++)
	{
		for(int j=0;j<img->w;j++)
		{
			Uint32 pix = getpixel(img, j, i); //two last param are pixel coordinates

			//Initializing rgb components for current pixel color
			SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);
            		//Translating current colors to greyscaled ones
			rpix = (max(rpix,bpix,rpix)+min(rpix,bpix,gpix))/2;
            		bwthreshold += (rpix);

    		}
	}

    //Bwthreshold is calculated as the average color of the picture
    //It allows the program to detect the text even on a dark background
    //BUT the text HAS to be DARKER than the background
    bwthreshold /= nbPix;


    //So this big loop mainly transform the image into a greyscaled image then in a B&W one.
    //Also, it does the "horizontal line detection" for the neural network later.

	for(int i=0;i<img->h;i++)
	{
        	Uint8 isWhiteLine = 1;

		for(int j=0;j<img->w;j++)
		{
			Uint32 pix = getpixel(img, j, i); //two last param are pixel coordinates

			//Initializing rgb components for current pixel color
			SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);
			//But we want a B&W image, so we have to supress the greyscale:
			if(rpix < bwthreshold) //If the pixel is sufficiently dark
			{
				rpix = 128;
				gpix = 0;
				bpix = 0;
                		isWhiteLine = 0; //there is pixel of text in the line
			}
			else
			{
				rpix = 255;
				gpix = rpix;
				bpix = rpix;
			}

			//Setting new B&W colors to img
			putpixel(img, j, i, SDL_MapRGB(img->format, rpix, gpix, bpix));

            		//Updating tempLine
		}

		if(isWhiteLine == 1) //If the line  is white, then we are not parsing text
	    {
            if(isptl == 1)// If we were parsing text the pixel line before
            {
                isptl = 0; //Then we are not anymore
                *nbLines = *nbLines + 1; //We increment the number of lines we read
        		for(int j=0;j<img->w;j++) //We draw a red line
	    		    putpixel(img, j, i-1, SDL_MapRGB(img->format, 255, 0, 0));
                if(tempMax > maxHeight) //We test the height of this line
                    maxHeight = tempMax; //And compare it to the greater we have
                tempMax = 0; //Resetting the temp height of the line
            }
        }
        else if(isptl == 0)
        {
            isptl = 1;
            tempMax++;
    		for(int j=0;j<img->w;j++)
			    putpixel(img, j, i, SDL_MapRGB(img->format, 255, 0, 0));
        }
        else
        {
            tempMax++;
        }
	}

	int fullLine[maxHeight][img->w];
	for(int i = 0;i<maxHeight;i++)
	{
		for(int j = 0;j<img->w;j++)
			fullLine[i][j] = 0;
	}
	unsigned long tempHeight = 0;
	for(int i=0;i<img->h;i++)
	{
        	Uint8 isWhiteLine = 1;

		for(int j=0;j<img->w;j++)
		{
			Uint32 pix = getpixel(img, j, i); //two last param are pixel coordinates

			//Initializing rgb components for current pixel color
			SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);
			//But we want a B&W image, so we have to supress the greyscale:
			if(rpix == 128) //If the pixel is sufficiently dark
			{
                		isWhiteLine = 0; //there is pixel of text in the line
			}
            		tempLine[j] = rpix;
		}

		if(isWhiteLine == 1) //If the line  is white, then we are not parsing text
	    	{

            		if(isptl == 1)// If we were parsing text the pixel line before
            		{
                		isptl = 0; //Then we are not anymore
				for(int k=0;k<img->w;k++)
				{
					printf("k : %d\n", k);
					fullLine[tempHeight][k] = tempLine[k];
				}
				printf("COUCOU");
				//Insert a rowSight call
				int k=0;
				while(fullLine[tempHeight/2][k] != 128)
					k++;
				rowSight(img, k, tempHeight/2+i);
            		}
			tempHeight = 0;
        	}
        	else if(isptl == 0)
        	{
			tempHeight++;
            		isptl = 1;
        	}
        	else
			tempHeight++;
	}

       free(tempLine);

}

void rowSight(SDL_Surface *img, unsigned long x, unsigned long y)
{
	printf("x:%lu  y:%lu \n", x, y);
	//This function is a recursive character recognition function
	//It is like the bucket fill tool in GIMP or Photoshop
    

	Uint32 pix = getpixel(img, x-1, y);
	Uint8 rpix=0, gpix=0, bpix=0;
	SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);
			

    	if(rpix == 128)
	{
		putpixel(img, x-1, y, SDL_MapRGB(img->format, 0, 0, 0));
		rowSight(img, x-1, y);
	}

	pix = getpixel(img, x+1, y);
	SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);


	if(rpix == 128)
	{
		putpixel(img, x+1, y, SDL_MapRGB(img->format, 0, 0, 0));
		rowSight(img, x+1, y);
	}

	pix = getpixel(img, x, y-1);
	SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);

	if(rpix == 128)
	{
		putpixel(img, x, y-1, SDL_MapRGB(img->format, 0, 0, 0));
		rowSight(img, x, y-1);
	}

	pix = getpixel(img, x, y+1);
	SDL_GetRGB(pix, img->format, &rpix, &gpix, &bpix);

	if(rpix == 128)
	{
		putpixel(img, x, y+1, SDL_MapRGB(img->format, 0, 0, 0));
		rowSight(img, x, y+1);
	}
}
