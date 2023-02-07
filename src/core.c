
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd_screen_init (fdScreen* s) {
	s->mode = FD_NONE;
	ng_rect_init(&s->rect, 0, 0, 640, 480); // 4:3
	ng_grid_init(&s->char_grid, &s->rect, 80, 30); // 80x30 8x16 chars 4:3
	ng_grid_init(&s->tile_grid, &s->rect, 40, 30); // 40x30 16x16 tiles 4:3
	ng_color_init(&s->background_color, 0, 0, 0);
	ng_color_init(&s->draw_color, 255, 255, 255);
}

void fd_core_init (fdCore* c) {
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		ng_here();
		printf("can't init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	ng_time_init(&c->time);
	
	if (!ng_graphics_init(&c->graphics, "Fire Days Demo", 640, 480)) {
		ng_here();
		printf("can't init graphics\n");
		exit(EXIT_FAILURE);
	}
	//TODO image bank
	
	//TODO audio
	//TODO channels
	//TODO clip bank
	
	ng_event_init(&c->event, &c->graphics);
}

void fd_core_quit (fdCore* c) {
	ng_graphics_quit(&c->graphics);
	
	SDL_Quit();
}

