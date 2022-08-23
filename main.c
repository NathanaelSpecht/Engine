/*
    Trees In Space Engine (TIS) game engine functions.
    Copyright (C) 2022  Trees in Space

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    Trees in Space  treesinspacecompany@gmail.com
*/

// ============== Include ==============

#include "SDL.h"
#include <tgmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// ============== Define ==============

#define DEBUG(a); printf("%s:%d %s\n", __FILE__, __LINE__, a);
#define ISNULL(a,b); if (a == NULL) { DEBUG(b); exit(EXIT_FAILURE); }

// ============== Type ==============

// unoptimized, [u]nsigned integer types
typedef unsigned char uchar;
typedef unsigned int uint;

// signed/[u]nsigned integer types, at least 8/16/32/64 bits
// optimized for cpu speed
typedef int_fast8_t fast8;
typedef int_fast16_t fast16;
typedef int_fast32_t fast32;
typedef int_fast64_t fast64;
typedef uint_fast8_t ufast8;
typedef uint_fast16_t ufast16;
typedef uint_fast32_t ufast32;
typedef uint_fast64_t ufast64;

// optimized for ram space
typedef int_least8_t least8;
typedef int_least16_t least16;
typedef int_least32_t least32;
typedef int_least64_t least64;
typedef uint_least8_t uleast8;
typedef uint_least16_t uleast16;
typedef uint_least32_t uleast32;
typedef uint_least64_t uleast64;

// ============== Struct ==============

typedef struct Box {
	int x, y, c, r; // x, y, columns, rows
} Box;

typedef struct Image {
	char* name;
	int c, r;
	int uw, uh; // image: unit width and height
	SDL_Texture* texture;
} Image;

typedef struct State {
	char* name;
	float w, h;
	int color1, color2, color3;
	Image* image;
} State;

typedef struct Sprite {
	int id;
	float x, y; // center
	int angle;
	State* state;
} Sprite;

typedef struct Camera {
	float wx, wy, ww, wh; //world-units: center x/y, width/height
	int angle;
	int sx, sy, sc, sr; //screen-units: top-left x/y, columns, rows
	Sprite* target;
} Camera;

typedef struct Graphics {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int w, h;
	int c, r;
	int rotationspeed;
	float movespeed;
	int colorkey;
	int bgcolor;
	int txtcolor;
} Graphics;

// ============= Function ============

Image* newImage (const char*, const char*, int, int, const Graphics*);
void freeImage (Image*);

State* newState (const char*, float, float, int, int, int, const char*, Image**);
void freeState (State*);

Sprite* newSprite (int, float, float, int, const char*, State**);
void freeSprite (Sprite*);

Camera* newCamera (int, int, int, int, int, Sprite**);
void moveCamera (float, float, Camera*);
void moveCameraTarget (float, float, Camera*);
void rotateCamera (int, Camera*);
void rotateCameraTarget (int, Camera*);
void freeCamera (Camera*);

void renderString (const char*, const Box*, Image*, const Graphics*);
void renderSprite (Sprite*, Camera*, const Graphics*);

int addAngle (int, int);
void move (float*, float*, float, float, int);
void rotate (float*, float*, int);

int color (int, int, int);
int red (int);
int green (int);
int blue (int);

char* copyString (const char*);
char* subString (const char*, int, int);
bool equalsString (const char*, const char*);

char* readFile (const char*, const char*);
void writeFile (const char*, const char*, const char*);

// ==================== Main ==============

int main (int argc, char** argv) {
	printf("Starting app\n");
	
	Graphics g = {
		.window = NULL,
		.renderer = NULL,
		.w = 12, .h = 16,
		.c = 80, .r = 30,
		.rotationspeed = 15,
		.movespeed = 0.16,
		.colorkey = 0x000000,
		.bgcolor = 0x000000,
		.txtcolor = 0x00ff00
	};

	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		DEBUG(SDL_GetError());
		return(EXIT_FAILURE);
	}
	
	g.window = SDL_CreateWindow("Example App", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		g.w * g.c, g.h * g.r, 0
	);
	ISNULL(g.window, SDL_GetError());
	
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);
	ISNULL(g.renderer, SDL_GetError());
	
	Image** images = NULL;
	images = malloc(4 * sizeof(Image*));
	ISNULL(images, "out of memory");
	
	images[0] = newImage("ansi", "ansi.bmp", 16, 8, &g);
	images[1] = newImage("tree", "tree.bmp", 16, 2, &g);
	images[2] = newImage("cylinder", "cylinder.bmp", 1, 1, &g);
	images[3] = NULL;
	
	State** states = NULL;
	states = malloc(5 * sizeof(State*));
	ISNULL(states, "out of memory");
	
	states[0] = newState("tree-green", 1.0, 1.0, color(200, 100, 50), color(50, 200, 25), 0, "tree", images);
	states[1] = newState("tree-dead", 1.0, 1.0, color(200, 50, 100), 0, 0, "tree", images);
	states[2] = newState("tree-onfire", 1.0, 1.0, color(200, 25, 50), color(25, 50, 200), 0, "tree", images);
	states[3] = newState("cylinder", 1.0, 1.0, color(50, 50, 50), 0, 0, "cylinder", images);
	states[4] = NULL;
	
	Sprite** sprites = NULL;
	sprites = malloc(5 * sizeof(Sprite*));
	ISNULL(sprites, "out of memory");
	
	sprites[0] = newSprite(0, 0.0, 0.0, 0, "tree-green", states);
	sprites[1] = newSprite(1, 1.0, 0.0, 30, "tree-dead", states);
	sprites[2] = newSprite(2, 0.0, 1.0, 90, "tree-onfire", states);
	sprites[3] = newSprite(3, 1.0, 1.0, 120, "cylinder", states);
	sprites[4] = NULL;
	
	Camera* camera = NULL;
	camera = newCamera(0, 0, 80, 30, 0, sprites);

	SDL_Event event;
	while (true) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				goto quit;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: {
						goto quit;
						break;
					} case SDLK_PERIOD: {
						rotateCamera(g.rotationspeed, camera);
						break;
					} case SDLK_COMMA: {
						rotateCamera(-(g.rotationspeed), camera);
						break;
					} case SDLK_SLASH: {
						// return camera to target, and turn in direction target is facing.
						camera->wx = -(camera->target->x);
						camera->wy = -(camera->target->y);
						camera->angle = camera->target->angle;
						break;
					} case SDLK_RIGHT: {
						moveCamera(-(g.movespeed), 0.0, camera);
						break;
					} case SDLK_LEFT: {
						moveCamera(g.movespeed, 0.0, camera);
						break;
					} case SDLK_UP: {
						moveCamera(0.0, -(g.movespeed), camera);
						break;
					} case SDLK_DOWN: {
						moveCamera(0.0, g.movespeed, camera);
						break;
					} case SDLK_e: {
						rotateCameraTarget(-(g.rotationspeed), camera);
						break;
					} case SDLK_q: {
						rotateCameraTarget(g.rotationspeed, camera);
						break;
					} case SDLK_d: {
						moveCameraTarget(g.movespeed, 0.0, camera);
						break;
					} case SDLK_a: {
						moveCameraTarget(-(g.movespeed), 0.0, camera);
						break;
					} case SDLK_w: {
						moveCameraTarget(0.0, g.movespeed, camera);
						break;
					} case SDLK_s: {
						moveCameraTarget(0.0, -(g.movespeed), camera);
						break;
					}
				}
			}
		}
		
		SDL_SetRenderDrawColor(g.renderer, red(g.bgcolor), green(g.bgcolor), blue(g.bgcolor), 255);
		SDL_RenderClear(g.renderer);
		
		for (int i = 0; sprites[i] != NULL; i++) {
			renderSprite(sprites[i], camera, &g);
		}
		
		SDL_RenderPresent(g.renderer);
		SDL_Delay(10);
	}
	
quit:
	printf("Closing app\n");
	
	freeCamera(camera);
	
	for (int i = 0; sprites[i] != NULL; i++) {
		freeSprite(sprites[i]);
	}
	free(sprites);
	
	for (int i = 0; states[i] != NULL; i++) {
		freeState(states[i]);
	}
	free(states);
	
	for (int i = 0; images[i] != NULL; i++) {
		freeImage(images[i]);
	}
	free(images);
	
	SDL_DestroyRenderer(g.renderer);
	SDL_DestroyWindow(g.window);
	SDL_Quit();
	
	return 0;
}

// =========== Render =============

void renderString (const char* s, const Box* box, Image* image, const Graphics* g) {
	SDL_Rect src;
	SDL_Rect dest;
	
	src.x = 0;
	src.y = 0;
	src.w = image->uw;
	src.h = image->uh;
	
	dest.x = g->w * box->x;
	dest.y = g->h * box->y;
	dest.w = g->w;
	dest.h = g->h;
	
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
			dest.x = g->w * (box->x + tx);
			dest.y = g->h * (box->y + ty);
			SDL_SetTextureColorMod(image->texture, red(g->txtcolor), green(g->txtcolor), blue(g->txtcolor));
			SDL_RenderCopy(g->renderer, image->texture, &src, &dest);
		}
	}
}

void renderSprite (Sprite* sprite, Camera* camera, const Graphics* g) {
	//find dest from sprite and camera.
	SDL_Rect dest;
	{	
		//let d x/y be center and w/h be half-width/height.
		float dx = sprite->x;
		float dy = sprite->y;
		float dw = sprite->state->w * 0.5;
		float dh = sprite->state->h * 0.5;
		
		//rotate sprite around camera position by camera angle.
		dx += camera->wx;
		dy += camera->wy;
		rotate(&dx, &dy, -camera->angle);
		
		//transform sprite x/y in world to x/y on screen.
		float sw = (float)(camera->sc * g->w) * 0.5;
		float sh = (float)(camera->sr * g->h) * 0.5;
		dx *= (sw / (camera->ww * 0.5));
		dy *= (sh / (camera->wh * 0.5));
		dy = -dy;
		dx += sw;
		dy += sh;
		
		//scale sprite from camera axes in world to camera axes on screen.
		dw *= (sw / (camera->ww * 0.5));
		dh *= (sh / (camera->wh * 0.5));
		
		//let d x/y be top-left and w/h be width/height.
		dx = dx - dw;
		dy = dy - dh;
		dw = dw * 2.0;
		dh = dh * 2.0;
		
		if (dw < 1.0 || dh < 1.0 || dx < -8000.0 || dx > 8000.0 || dy < -8000.0 || dy > 8000.0) {
			//sprite culled bc not visible. NOT an error.
			return;
		}
		
		dest.x = (int)dx;
		dest.y = (int)dy;
		dest.w = (int)dw;
		dest.h = (int)dh;
	}
	
	Image* image = sprite->state->image;
	SDL_Rect src;
	
	src.w = image->uw;
	src.h = image->uh;
	
	int i = addAngle(sprite->angle, -camera->angle) / (360/image->c);
	if (i >= image->c) {
		i = image->c - 1;
	}
	src.x = src.w * i;
	
	int c1 = sprite->state->color1;
	int c2 = sprite->state->color2;
	int c3 = sprite->state->color3;
	if (c1 == 0 && c2 == 0 && c3 == 0) {
		SDL_SetTextureColorMod(image->texture, 255, 255, 255);
		src.y = 0;
		SDL_RenderCopy(g->renderer, image->texture, &src, &dest);
	} else {
		if (c1 != 0) {
			SDL_SetTextureColorMod(image->texture, red(c1), green(c1), blue(c1));
			src.y = src.h * 0;
			SDL_RenderCopy(g->renderer, image->texture, &src, &dest);
		}
		
		if (c2 != 0) {
			SDL_SetTextureColorMod(image->texture, red(c2), green(c2), blue(c2));
			src.y = src.h * 1;
			SDL_RenderCopy(g->renderer, image->texture, &src, &dest);
		}
		
		if (c3 != 0) {
			SDL_SetTextureColorMod(image->texture, red(c3), green(c3), blue(c3));
			src.y = src.h * 2;
			SDL_RenderCopy(g->renderer, image->texture, &src, &dest);
		}
	}
}

// =============== Struct ===============

Image* newImage (const char* name, const char* filename, int c, int r, const Graphics* g) {
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	Image* image = NULL;
	
	surface = SDL_LoadBMP(filename);
	ISNULL(surface, SDL_GetError());
	
	int image_uw = surface->w / c;
	int image_uh = surface->h / r;
	
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, red(g->colorkey), green(g->colorkey), blue(g->colorkey))) != 0) {
		DEBUG(SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	texture = SDL_CreateTextureFromSurface(g->renderer, surface);
	ISNULL(texture, SDL_GetError());
	
	SDL_FreeSurface(surface);
	
	image = malloc(sizeof(Image));
	ISNULL(image, "out of memory");
	
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

State* newState (const char* name, float w, float h, int color1, int color2, int color3, const char* image, Image** images) {
	State* state = NULL;
	
	state = malloc(sizeof(State));
	ISNULL(state, "out of memory");
	
	state->name = copyString(name);
	state->w = w;
	state->h = h;
	state->color1 = color1;
	state->color2 = color2;
	state->color3 = color3;
	
	for (int i = 0; images[i] != NULL; i++) {
		if (equalsString(images[i]->name, image)) {
			state->image = images[i];
		}
	}
	
	return state;
}

void freeState (State* state) {
	free(state->name);
	free(state);
}

Sprite* newSprite (int id, float x, float y, int angle, const char* state, State** states) {
	Sprite* sprite = NULL;
	
	sprite = malloc(sizeof(Sprite));
	ISNULL(sprite, "out of memory");
	
	sprite->id = id;
	sprite->x = x;
	sprite->y = y;
	sprite->angle = angle;
	
	sprite->state = NULL;
	
	for (int i = 0; states[i] != NULL; i++) {
		if (equalsString(states[i]->name, state)) {
			sprite->state = states[i];
		}
	}
	
	return sprite;
}

void freeSprite (Sprite* sprite) {
	free(sprite);
}

Camera* newCamera (int x, int y, int c, int r, int spriteID, Sprite** sprites) {
	Camera* camera = NULL;
	
	camera = malloc(sizeof(Camera));
	ISNULL(camera, "out of memory");
	
	camera->sx = x;
	camera->sy = y;
	camera->sc = c;
	camera->sr = r;
	
	camera->wx = 0.0;
	camera->wy = 0.0;
	camera->ww = ((float)c)*0.5;
	camera->wh = ((float)r)*0.5;
	camera->angle = 0;
	camera->target = NULL;
	
	for (int i = 0; sprites[i] != NULL; i++) {
		if (sprites[i]->id == spriteID) {
			camera->wx = -(sprites[i]->x);
			camera->wy = -(sprites[i]->y);
			camera->ww = sprites[i]->state->w * 16.0;
			camera->wh = sprites[i]->state->h * 6.0;
			camera->angle = sprites[i]->angle;
			camera->target = sprites[i];
		}
	}
	
	return camera;
}

void moveCamera (float u, float v, Camera* camera) {
	move(&(camera->wx), &(camera->wy), u, v, camera->angle);
}

void moveCameraTarget (float u, float v, Camera* camera) {
	move(&(camera->target->x), &(camera->target->y), u, v, camera->angle);
	move(&(camera->wx), &(camera->wy), -u, -v, camera->angle);
}

void rotateCamera (int angle, Camera* camera) {
	camera->angle = addAngle(camera->angle, angle);
}

void rotateCameraTarget (int angle, Camera* camera) {
	camera->target->angle = addAngle(camera->target->angle, angle);
	//camera->angle = addAngle(camera->angle, angle);
}

void freeCamera (Camera* camera) {
	free(camera);
}

// ================ Function ================

int addAngle (int angle, int change) {
	return (angle + 360 + change) % 360;
}

void move (float* px, float* py, float u, float v, int angle) {
	//let u (x,y) and v (x,y) be the x and y axis, rotated by angle degrees.
	float ux = 1.0;
	float uy = 0.0;
	float vx = 0.0;
	float vy = 1.0;
	rotate(&ux, &uy, angle);
	rotate(&vx, &vy, angle);
	
	//move p (x,y) along u (x,y) and v (x,y) by u and v units.
	*px += (u * ux) + (v * vx);
	*py += (u * uy) + (v * vy);
}

void rotate (float* vx, float* vy, int angle) {
	//convert angle from degrees to radians.
	float r = (float)angle * (3.14/180.0);
	
	// rotate v (x,y) about the origin by r radians.
	float x = *vx;
	float y = *vy;
	float cosr = cos(r);
	float sinr = sin(r);
	*vx = (x * cosr) - (y * sinr);
	*vy = (x * sinr) + (y * cosr);
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
	ISNULL(s, "out of memory");
	s[0] = '\0';
	if (a != NULL) {
		for(int i = 0; a[i] != '\0'; i++) {
			s = realloc(s, i+2);
			ISNULL(s, "out of memory");
			s[i] = a[i];
			s[i+1] = '\0';
		}
	}
	
	return s;
}

char* subString (const char* a, int i, int n) {
	char* s = NULL;
	
	s = malloc(1);
	ISNULL(s, "out of memory");
	s[0] = '\0';
	if (a != NULL && i >= 0) {
		for (int k = 0; a[k] != '\0'; k++) {
			if (k >= i && k-i < n) {
				s = realloc(s, (k-i)+2);
				ISNULL(s, "out of memory");
				s[k-i] = a[k];
				s[(k-i)+1] = '\0';
			} else if (k-i >= n) {
				break;
			}
		}
	}
	
	return s;
}

bool equalsString (const char* a, const char* b) {
	if (a == NULL && b == NULL) {
		return true;
	} else if (a == NULL || b == NULL) {
		return false;
	}
	
	for (int i = 0; ; i++) {
		if (a[i] == '\0' && b[i] == '\0') {
			return true;
		} else if (a[i] != b[i]) {
			return false;
		}
	}
}

char* readFile (const char* filename, const char* options) {
	char* s = NULL;
	s = malloc(1);
	ISNULL(s, "out of memory");
	s[0] = '\0';
	
	FILE* f = NULL;
	f = fopen(filename, options);
	ISNULL(f, "cannot open file");
	
	int c = 0;
	for (int i = 0; (c = fgetc(f)) != EOF; i++) {
		s = realloc(s, i+2);
		if (s == NULL) {
			DEBUG("out of memory");
			fclose(f);
			exit(EXIT_FAILURE);
		}
		s[i] = (char)c;
		s[i+1] = '\0';
	}
	
	if (ferror(f)) {
		DEBUG("cannot read file");
		fclose(f);
		exit(EXIT_FAILURE);
	} else {
		fclose(f);
	}
	
	return s;
}

void writeFile (const char* s, const char* filename, const char* options) {
	FILE* f = NULL;
	f = fopen(filename, options);
	ISNULL(f, "cannot open file");
	
	if (s != NULL) {
		for (int i = 0; s[i] != '\0'; i++) {
			if (fputc(s[i], f) == EOF) {
				DEBUG("cannot write file");
				fclose(f);
				exit(EXIT_FAILURE);
			}
		}
	}
	
	fclose(f);
}

