
/*  Example use of TIS.
    Copyright (C) 2022  Trees in Space

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    
    Trees in Space  treesinspacecompany@gmail.com
*/

#include "tis.h"

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
	
	g.window = SDL_CreateWindow("app", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		g.w * g.c, g.h * g.r, 0
	);
	ISNULL(g.window, SDL_GetError());
	
	g.renderer = SDL_CreateRenderer(g.window, -1, 0);
	ISNULL(g.renderer, SDL_GetError());
	
	Image** images = NULL;
	images = malloc(4 * sizeof(Image*));
	ISNULL(images, "out of memory");
	
	images[0] = newImage("print", "print.bmp", 32, 8, &g);
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

