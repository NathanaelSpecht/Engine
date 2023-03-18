
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
		audio.volume = 1.0f;
		time.init();
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Color background_color;
	background_color.init(0, 0, 0);
	ng::Color draw_color;
	draw_color.init(32, 32, 32);
	ng::Color color_key;
	color_key.init(0, 0, 0);
	
	ng::Color rect_color;
	rect_color.init(64, 16, 0);
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
	channel.volume = 1.0f;
	
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
	
	ng::Tileset tileset;
	tileset.init(&image, &image.rect, 32, 6);
	tileset.row_offset = -1;
	
	int line_w, line_h;
	line_w = 8;
	line_h = 16;
	ng::Rect text_rect;
	text_rect.init(line_w, line_h, graphics.rect.w-(line_w*2), graphics.rect.h-(line_h*2));
	ng::Grid text_grid;
	text_grid.init(&text_rect, text_rect.w/line_w, text_rect.h/line_h);
	
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
						case SDL_SCANCODE_PERIOD:
							channel.volume = ng::clamp(channel.volume + 0.05f, 0.0f, 1.0f);
							break;
						case SDL_SCANCODE_COMMA:
							channel.volume = ng::clamp(channel.volume - 0.05f, 0.0f, 1.0f);
							break;
						case SDL_SCANCODE_M:
							audio.volume = ng::clamp(audio.volume + 0.05f, 0.0f, 1.0f);
							break;
						case SDL_SCANCODE_N:
							audio.volume = ng::clamp(audio.volume - 0.05f, 0.0f, 1.0f);
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
		
		rect.x += (right - left) * 3;
		rect.y += (down - up) * 3;
		
		try {
			graphics.set_color(&background_color);
			graphics.clear();
			
			graphics.set_color(&draw_color);
			graphics.draw_rect(&text_rect, ng::DrawFill);
			
			graphics.set_color(&rect_color);
			graphics.draw_rect(&rect, ng::DrawFill);
			
			graphics.draw_text(&tileset,
				"My Friend.--Welcome to the Carpathians. I am anxiously expecting you. "
				"Sleep well to-night. At three to-morrow the diligence will start for "
				"Bukovina; a place on it is kept for you. At the Borgo Pass my carriage "
				"will await you and will bring you to me. I trust that your journey from "
				"London has been a happy one, and that you will enjoy your stay in my "
				"beautiful land.\n"
				"                                                        Your friend,\n"
				"                                                        Dracula.",
				&text_rect, &text_grid);
			
			//graphics.draw_image(&image, &image.rect, &rect);
			
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


