
/* Copyright (C) 2023 Nathanael Specht */

#include "ng.h"
#include <iostream>

int main (int argc, char** argv) {
	ng::Event event;
	ng::Graphics graphics;
	ng::Audio audio;
	ng::Time time;
	
	try {
		ng::init();
		event.init(&graphics);
		graphics.init("Fire Days Demo", 640, 480);
		audio.init();
		time.init();
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Color background_color;
	background_color.init(0, 0, 0);
	ng::Color draw_color;
	draw_color.init(255, 255, 255);
	ng::Color color_key;
	color_key.init(0, 0, 0);
	ng::Rect rect;
	rect.init((graphics.rect.w/2)-256, (graphics.rect.h/2)-80, 256*2, 80*2);
	
	ng::Image image;
	ng::Clip clip;
	
	const char* file;
	try {
		image.init(&graphics, file="game-data/text.bmp", &color_key);
		clip.init(&audio, file="game-data/Corncob.wav");
	} catch (const std::exception& ex) {
		std::cout << "error loading \"" << file << "\":\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Channel channel;
	channel.init();
	
	try {
		channel.play_sound(&clip, ng::SoundLoop);
	} catch (const std::exception& ex) {
		std::cout << "error configuring data:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	int up, down, left, right;
	up = 0;
	down = 0;
	left = 0;
	right = 0;
	
	while (true) {
		while (event.next()) {
			if (event.mode == ng::Quit) {
				goto quit;
			}
			
			switch (event.mode) {
				case ng::Quit:
					goto quit;
					break;
				case ng::WindowEvent:
					rect.x = (graphics.rect.w/2)-(rect.w/2);
					rect.y = (graphics.rect.h/2)-(rect.h/2);
					break;
				case ng::KeyPress: {
					switch (event.key.scancode) {
						case SDL_SCANCODE_SPACE:
							rect.x = (graphics.rect.w/2)-(rect.w/2);
							rect.y = (graphics.rect.h/2)-(rect.h/2);
							up = 0;
							down = 0;
							left = 0;
							right = 0;
							break;
						case SDL_SCANCODE_W:
							up = 1;
							break;
						case SDL_SCANCODE_S:
							down = 1;
							break;
						case SDL_SCANCODE_A:
							left = 1;
							break;
						case SDL_SCANCODE_D:
							right = 1;
							break;
						default: {}
					}
					break;
				}
				case ng::KeyRelease: {
					switch (event.key.scancode) {
						case SDL_SCANCODE_W:
							up = 0;
							break;
						case SDL_SCANCODE_S:
							down = 0;
							break;
						case SDL_SCANCODE_A:
							left = 0;
							break;
						case SDL_SCANCODE_D:
							right = 0;
							break;
						default: {}
					}
					break;
				}
				default: {}
			}
		}
		
		rect.x += right - left;
		rect.y += down - up;
		
		try {
			graphics.set_color(&background_color);
			graphics.clear();
			
			graphics.set_color(&draw_color);
			graphics.draw_image(&image, &image.rect, &rect);
			
			graphics.draw();
			
		} catch (const std::exception& ex) {
			std::cout << "error drawing graphics:\n"
				<< ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		try {
			audio.clear(time.delta);
			audio.mix_channel(&channel);
			audio.play();
			
		} catch (const std::exception& ex) {
			std::cout << "error playing audio:\n"
				<< ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		time.tick();
	}

quit:
	image.quit();
	graphics.quit();
	
	clip.quit();
	channel.quit();
	audio.quit();
	
	ng::quit();
	
	return EXIT_SUCCESS;
};


