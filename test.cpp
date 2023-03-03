
/* Copyright (C) 2023 Nathanael Specht */

#include "ng.h"

int main (int argc, char** argv) {
	ngTime time;
	ngGraphics graphics;
	//TODO audio & channels
	ngEvent event;
	
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		ng_here();
		printf("can't init SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	ng_time_init(&time);
	
	if (!ng_graphics_init(&graphics, "Fire Days Demo", 640, 480)) {
		ng_here();
		printf("can't init graphics\n");
		exit(EXIT_FAILURE);
	}
	
	//TODO audio & channels
	
	ng_event_init(&event, &graphics);
	
	ngColor background_color;
	ng_color_init(&background_color, 0, 0, 0);
	ngColor draw_color;
	ng_color_init(&draw_color, 255, 255, 255);
	ngRect rect;
	ng_rect_init(&rect, 250, 200, 150, 100);
	
	while (true) {
		while (ng_event_next(&event)) {
			if (event.mode == NG_QUIT) {
				goto quit;
			}
			
			// handle events
		}
		
		{
			ng_graphics_color(&graphics, &background_color);
			ng_graphics_clear(&graphics);
			
			ng_graphics_color(&graphics, &draw_color);
			ng_draw_rect(&graphics, &rect, NG_FILL);
			
			ng_graphics_draw(&graphics);
		}
		
		{ //TODO audio
			/*
			ng_audio_clear(&a);
			ng_audio_mix_channel(&a, &music);
			ng_audio_mix_channel(&a, &sound);
			ng_audio_queue(&a);
			*/
		}
		
		ng_time_tick(&time);
	}

quit:
	ng_graphics_quit(&graphics);
	
	SDL_Quit();
	return EXIT_SUCCESS;
};


