
/* Copyright (C) 2023 Nathanael Specht */

#include "ng.h"
#include <iostream>

int main (int argc, char** argv) {
	ng::Graphics graphics;
	ng::Audio audio;
	ng::Event event;
	ng::Time time;
	
	try {
		ng::init();
		graphics.open("Fire Days Demo", 640.0, 480.0);
		audio.open();
		event.reset(&graphics);
		time.reset();
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Color color_key;
	color_key.set(0, 0, 0);
	ng::Image image;
	ng::Clip clip;
	
	const char* file;
	try {
		image.load(&graphics, file="game-data/text.bmp", &color_key);
		clip.load(&audio, file="game-data/Corncob.wav");
	} catch (const std::exception& ex) {
		std::cout << "error loading \"" << file << "\":\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Channel channel;
	channel.volume = 1.0f;
	audio.volume = 1.0f;
	
	try {
		channel.play_sound(&clip, ng::SoundLoop);
	} catch (const std::exception& ex) {
		std::cout << "error configuring data:\n"
			<< ex.what() << "\n";
		exit(EXIT_FAILURE);
	}
	
	ng::Tileset tileset;
	tileset.set_c(&image, &image.rect, 32.0, 6.0);
	tileset.offset.set2(0.0, -1.0);
	
	ng::Canvas window;
	window.set(&graphics);
	
	ng::Color background_color;
	background_color.set(16, 0, 16);
	ng::Color draw_color;
	draw_color.set(32, 32, 32);
	ng::Color rect_color_true, rect_color_false;
	rect_color_true.set(64, 16, 0);
	rect_color_false.set(32, 0, 128);
	bool rect_contains_mouse = false;
	ng::Rect rect;
	rect.set2((window.space.rect.w*0.5)-256.0, (window.space.rect.h*0.5)-80.0, 256.0*2.0, 80.0*2.0);
	
	ng::Color text_color;
	text_color.set(196, 128, 0);
	double line_w, line_h;
	line_w = 12.0;
	line_h = 24.0;
	ng::Label label;
	label.set("My Friend.--Welcome to the Carpathians. I am anxiously expecting you. "
		"Sleep well to-night. At three to-morrow the diligence will start for "
		"Bukovina; a place on it is kept for you. At the Borgo Pass my carriage "
		"will await you and will bring you to me. I trust that your journey from "
		"London has been a happy one, and that you will enjoy your stay in my "
		"beautiful land.\n"
		"                           Your friend,\n"
		"                           DRACULA.",
		20.0, &text_color,
		line_w, line_h, window.space.rect.w-(line_w*2.0), window.space.rect.h-(line_h*2.0));
	
	ng::Color mouse_color;
	mouse_color.set(255, 255, 255);
	double up, down, left, right;
	up = 0.0;
	down = 0.0;
	left = 0.0;
	right = 0.0;
	ng::Vec mouse;
	mouse.set2(0.0, 0.0);
	
	ng::Color button_press_color, button_release_color;
	button_press_color.set(0, 32, 0);
	button_release_color.set(0, 100, 0);
	ng::Button button;
	button.set("Press Me!", 0.33, 440.0, 380.0, 200.0, 100.0);
	bool button_contains_mouse = false;
	
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
					mouse.set2(static_cast<double>(event.mouse.x),
						static_cast<double>(event.mouse.y));
					window.get_mouse(&mouse);
					rect_contains_mouse = rect.contains2(mouse.x, mouse.y);
					
					if (button.contains(&mouse)) {
						button.fill_color = button_press_color;
					} else {
						button.fill_color = button_release_color;
					}
					break;
				}
				case ng::MouseRelease: {
					button.fill_color = button_release_color;
					break;
				}
				default: {}
			}
		}
		
		rect.x += (right - left) * 2.0;
		rect.y += (down - up) * 2.0;
		
		try {
			graphics.set_color(&background_color);
			graphics.clear();
			
			graphics.set_color(&draw_color);
			window.draw_rect(&label.space.rect, ng::DrawFill);
			
			if (rect_contains_mouse) {
				graphics.set_color(&rect_color_true);
			} else {
				graphics.set_color(&rect_color_false);
			}
			window.draw_rect(&rect, ng::DrawFill);
			
			window.draw_button(&tileset, &button);
			window.draw_label(&tileset, &label);
			
			//graphics.draw_image(&image, &image.rect, &rect);
			
			graphics.set_color(&mouse_color);
			window.draw_point(mouse.x, mouse.y);
			
			graphics.draw();
			
		} catch (const std::exception& ex) {
			std::cout << "error drawing graphics:\n"
				<< ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		try {
			audio.clear(time.delta);
			//audio.mix_channel(&channel);
			audio.play();
			
		} catch (const std::exception& ex) {
			std::cout << "error playing audio:\n"
				<< ex.what() << "\n";
			exit(EXIT_FAILURE);
		}
		
		time.tick();
	}

quit:
	graphics.close();
	audio.close();
	ng::quit();
	
	return EXIT_SUCCESS;
};


