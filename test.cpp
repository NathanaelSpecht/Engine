
/* Copyright (C) 2023 Nathanael Specht */

#include "ng.h"
#include <cstdlib>

int main (int argc, char** argv) {
	ngTime t;
	ngGraphics g;
	//TODO audio & channels
	ngEvent e;
	
	try {
		ng::init();
		
		ng_time_init(&t);
		ng_graphics_init(&g, "Fire Days Demo", 640, 480);
		//TODO audio & channels
		ng_event_init(&e, &g);
		
	} catch (const std::exception& ex) {
		std::cout << NG_HERE << ": can't init: " << ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ngColor background_color;
	ng_color_init(&background_color, 0, 0, 0);
	ngColor draw_color;
	ng_color_init(&draw_color, 255, 255, 255);
	ngRect rect;
	ng_rect_init(&rect, 250, 200, 150, 100);
	
	while (true) {
		while (ng_event_next(&e)) {
			if (e.mode == NG_QUIT) {
				goto quit;
			}
			
			// handle events
		}
		
		try {
			ng_graphics_color(&g, &background_color);
			ng_graphics_clear(&g);
			
			ng_graphics_color(&g, &draw_color);
			ng_draw_rect(&g, &rect, NG_FILL);
			
			ng_graphics_draw(&g);
		} catch (const std::exception& ex) {
			std::cout << NG_HERE << ": graphics error: " << ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		try {
			/*
			ng_audio_clear(&a);
			ng_audio_mix_channel(&a, &music);
			ng_audio_mix_channel(&a, &sound);
			ng_audio_queue(&a);
			*/
		} catch (const std::exception& ex) {
			std::cout << NG_HERE << ": audio error: " << ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		ng_time_tick(&t);
	}

quit:
	ng_graphics_quit(&g);
	ng::quit();
	
	return EXIT_SUCCESS;
};


