
/* Copyright (C) 2023 Nathanael Specht */

#include "ng.h"
#include <iostream>

int main (int argc, char** argv) {
	ng::Time time;
	ng::Graphics graphics;
	//TODO audio & channels
	ng::Event event;
	
	try {
		ng::init();
		
		time.init();
		graphics.init("Fire Days Demo", 640, 480);
		//TODO audio & channels
		event.init(&graphics);
		
	} catch (const std::exception& ex) {
		std::cout << NG_HERE << ": can't init: " << ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Color background_color;
	background_color.init(0, 0, 0);
	ng::Color draw_color;
	draw_color.init(255, 255, 255);
	ng::Rect rect;
	rect.init(250, 200, 150, 100);
	
	while (true) {
		while (event.next()) {
			if (event.mode == ng::Quit) {
				goto quit;
			}
			
			// handle events
		}
		
		try {
			graphics.set_color(&background_color);
			graphics.clear();
			
			graphics.set_color(&draw_color);
			graphics.draw_rect(&rect, ng::DrawFill);
			
			graphics.draw();
			
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
		
		time.tick();
	}

quit:
	graphics.quit();
	ng::quit();
	
	return EXIT_SUCCESS;
};


