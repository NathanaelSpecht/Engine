
#include "SDL.h"
#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define debug(a); printf("%s:%d %s\n", __FILE__, __LINE__, a);
#define here(); printf("%s:%d\n", __FILE__, __LINE__);
#define isnull(a,b); if (a == NULL) { debug(b); exit(EXIT_FAILURE); }

typedef struct Box {
	int x, y, c, r; // x, y, columns, rows
} Box;

typedef struct Image {
	char* name;
	int c, r;
	int uw, uh; // image: unit width and height
	SDL_Texture* texture;
} Image;

Image* newImage (const char*, const char*, int, int);
void freeImage (Image*);
void renderString (const char*, const Box*, Image*);
int color (int, int, int);
int red (int);
int green (int);
int blue (int);
char* copyString (const char*);

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int UWIDTH = 12, UHEIGHT = 16; // unit width and height
int UCOLUMNS = 80, UROWS = 30; // unit columns and rows

int ROTATIONSPEED = 15;
float MOVESPEED = 0.16;

int COLORKEY = 0x000000;
int BGCOLOR = 0xffffff;
int TXTCOLOR = 0x0000ff;

int main (int argc, char** argv) {

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		debug(SDL_GetError());
		return(EXIT_FAILURE);
	}
	
	window = SDL_CreateWindow("Hello", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		UWIDTH * UCOLUMNS, UHEIGHT * UROWS, 0
	);
	isnull(window, SDL_GetError());
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	isnull(renderer, SDL_GetError());
	
	Image* ansi = NULL;
	ansi = newImage("ansi", "ansi.bmp", 16, 8);
	
	const char* text = "hello";
	Box textbox = {.x=37, .y=14, .c=5, .r=1};
	
	SDL_SetRenderDrawColor(renderer, red(BGCOLOR), green(BGCOLOR), blue(BGCOLOR), 255);
	SDL_RenderClear(renderer);
	
	renderString(text, &textbox, ansi);
	
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
	
	freeImage(ansi);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	printf("hello\n");
	
	return 0;
}

void renderString (const char* s, const Box* box, Image* image) {
	SDL_Rect src;
	SDL_Rect dest;
	
	src.x = 0;
	src.y = 0;
	src.w = image->uw;
	src.h = image->uh;
	
	dest.x = UWIDTH * box->x;
	dest.y = UHEIGHT * box->y;
	dest.w = UWIDTH;
	dest.h = UHEIGHT;
	
	int tx, ty; // text: x and y
	int itc, itr; // image: text: column and row
	
	for (int i = 0; s[i] != '\0'; i++) {
		tx = i % box->c;
		ty = (i / box->c) % box->r;
		itc = s[i] % image->c;
		itr = (s[i] / image->c) % image->r;
		if (itr >= 0) {
			src.x = image->uw * itc;
			src.y = image->uh * itr;
			dest.x = UWIDTH * (box->x + tx);
			dest.y = UHEIGHT * (box->y + ty);
			SDL_SetTextureColorMod(image->texture, red(TXTCOLOR), green(TXTCOLOR), blue(TXTCOLOR));
			SDL_RenderCopy(renderer, image->texture, &src, &dest);
		}
	}
}

Image* newImage (const char* name, const char* filename, int c, int r) {
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	Image* image = NULL;
	
	surface = SDL_LoadBMP(filename);
	isnull(surface, SDL_GetError());
	
	int image_uw = surface->w / c;
	int image_uh = surface->h / r;
	
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, red(COLORKEY), green(COLORKEY), blue(COLORKEY))) != 0) {
		debug(SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	isnull(texture, SDL_GetError());
	
	SDL_FreeSurface(surface);
	
	image = malloc(sizeof(Image));
	isnull(image, "out of memory");
	
	image->name = copyString(name);
	image->c = c;
	image->r = r;
	image->uw = image_uw;
	image->uh = image_uh;
	image->texture = texture;
	
	return image;
}

void freeImage (Image* image) {
	free(image->name);
	SDL_DestroyTexture(image->texture);
	free(image);
}

int color (int r, int g, int b) {
	return (r << 16) | (g << 8) | b;
}

int red (int color) {
	return (color >> 16) & 0xff;
}

int green (int color) {
	return (color >> 8) & 0xff;
}

int blue (int color) {
	return color & 0xff;
}

char* copyString (const char* a) {
	char* s = NULL;
	
	s = malloc(1);
	isnull(s, "out of memory");
	s[0] = '\0';
	if (a != NULL) {
		for(int i = 0; a[i] != '\0'; i++) {
			s = realloc(s, i+2);
			isnull(s, "out of memory");
			s[i] = a[i];
			s[i+1] = '\0';
		}
	}
	
	return s;
}

