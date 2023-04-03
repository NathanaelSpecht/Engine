
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
		graphics.init("Fire Days Demo", 640.0, 480.0);
		audio.init();
		audio.volume = 1.0f;
		time.init();
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Color color_key;
	color_key.init(0, 0, 0);
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
	
	double up, down, left, right;
	up = 0.0;
	down = 0.0;
	left = 0.0;
	right = 0.0;
	
	ng::Tileset tileset;
	tileset.init_c(&image, &image.rect, 32.0, 6.0);
	tileset.offset.init2(0.0, -1.0);
	
	ng::Canvas window;
	window.init(&graphics);
	
	ng::Color background_color;
	background_color.init(0, 0, 0);
	ng::Color draw_color;
	draw_color.init(32, 32, 32);
	ng::Color rect_color_true, rect_color_false;
	rect_color_true.init(64, 16, 0);
	rect_color_false.init(32, 0, 128);
	bool rect_contains_mouse = false;
	ng::Rect rect;
	rect.init2((window.space.rect.w*0.5)-256.0, (window.space.rect.h*0.5)-80.0, 256.0*2.0, 80.0*2.0);
	
	ng::Color text_color;
	text_color.init(196, 128, 0);
	double line_w, line_h;
	line_w = 12.0;
	line_h = 24.0;
	ng::Rect text_rect;
	text_rect.init2(line_w, line_h, window.space.rect.w-(line_w*2.0), window.space.rect.h-(line_h*2.0));
	ng::Space textbox;
	textbox.init2_i(&text_rect, line_w, line_h);
	
	ng::Color mouse_color;
	mouse_color.init(255, 255, 255);
	ng::Vec mouse;
	mouse.init2(0.0, 0.0);
	
	while (true) {
		while (event.next()) {
			if (event.mode == ng::Quit) {
				goto quit;
			}
			
			switch (event.mode) {
				case ng::Quit: {
					goto quit;
					break;
				}
				//case ng::WindowEvent: {
				//	rect.x = (window.space.rect.w*0.5)-(rect.w*0.5);
				//	rect.y = (window.space.rect.h*0.5)-(rect.h*0.5);
				//	break;
				//} 
				case ng::KeyPress: {
					switch (event.key.scancode) {
						case SDL_SCANCODE_SPACE:
							rect.x = (window.space.rect.w*0.5)-(rect.w*0.5);
							rect.y = (window.space.rect.h*0.5)-(rect.h*0.5);
							up = 0.0;
							down = 0.0;
							left = 0.0;
							right = 0.0;
							break;
						case SDL_SCANCODE_W:
							up = 1.0;
							break;
						case SDL_SCANCODE_S:
							down = 1.0;
							break;
						case SDL_SCANCODE_A:
							left = 1.0;
							break;
						case SDL_SCANCODE_D:
							right = 1.0;
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
							up = 0.0;
							break;
						case SDL_SCANCODE_S:
							down = 0.0;
							break;
						case SDL_SCANCODE_A:
							left = 0.0;
							break;
						case SDL_SCANCODE_D:
							right = 0.0;
							break;
						default: {}
					}
					break;
				}
				case ng::MousePress: {
					mouse.init2(static_cast<double>(event.mouse.x),
						static_cast<double>(event.mouse.y));
					window.get_mouse(&mouse);
					rect_contains_mouse = rect.contains2(mouse.x, mouse.y);
				}
				default: {}
			}
		}
		
		rect.x += (right - left) * 2.0;
		rect.y += (down - up) * 2.0;
		
		try {
			graphics.set_color(&background_color);
			window.clear();
			
			graphics.set_color(&draw_color);
			window.draw_rect(&text_rect, ng::DrawFill);
			
			if (rect_contains_mouse) {
				graphics.set_color(&rect_color_true);
			} else {
				graphics.set_color(&rect_color_false);
			}
			window.draw_rect(&rect, ng::DrawFill);
			
			tileset.image->set_color(&text_color);
			//tileset.image->set_angle(10.0);
			window.draw_text(&tileset, "Hello, World!", &textbox);
			/* window.draw_text(&tileset,
				"My Friend.--Welcome to the Carpathians. I am anxiously expecting you. "
				"Sleep well to-night. At three to-morrow the diligence will start for "
				"Bukovina; a place on it is kept for you. At the Borgo Pass my carriage "
				"will await you and will bring you to me. I trust that your journey from "
				"London has been a happy one, and that you will enjoy your stay in my "
				"beautiful land.\n"
				"                                                        Your friend,\n"
				"                                                        DRACULA.",
				&textbox);
			*/
			
			//graphics.draw_image(&image, &image.rect, &rect);
			
			graphics.set_color(&mouse_color);
			window.draw_point(mouse.x, mouse.y);
			
			window.draw();
			
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


