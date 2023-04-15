
// Copyright (C) 2022 - 2023 Nathanael Specht

#include "demo.h"
#include <iostream>

demo::Core::Core () {}

demo::Core::~Core () {}

void demo::Core::reset () {
	try {
		ng::init();
		this->graphics.open("Fire Days Demo", 640.0, 480.0);
		this->audio.open();
		this->event.reset(&this->graphics);
		this->time.reset();
		
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	{
		const char* file;
		try {
			ng::Color color_key;
			color_key.set(0, 0, 0);
			this->font_img.load(&this->graphics, file="game-data/text.bmp", &color_key);
			this->crazy_music.load(&this->audio, file="game-data/Corncob.wav");
			
		} catch (const std::exception& ex) {
			std::cout << "error loading \"" << file << "\":\n"
				<< ex.what();
			exit(EXIT_FAILURE);
		}
	}
	
	this->font.set(&this->font_img, 32.0, 6.0);
	this->font.offset.set(0.0, -1.0);
	
	this->music_channel.volume = 0.75;
	this->sound_channel.volume = 0.75;
	
	try {
		this->music_channel.play_sound(&this->crazy_music, ng::SoundLoop);
		
		this->screen.reset(this);
		
	} catch (const std::exception& ex) {
		std::cout << "error configuring data:\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->screen.set_mode(demo::TitleMode);
}

void demo::Core::loop () {
	ng::Color black;
	black.set(0, 0, 0);
	while (true) {
		while (this->event.next()) {
			if (this->event.mode == ng::Quit) {
				return;
			} else if (this->event.mode == ng::WindowEvent) {
				// optionally resize screens and menus to fit window.
				continue;
			}
			
			// Find place to process event, then consume event.
			this->screen.event(this);
			if (this->screen.mode == ng::None) {
				return;
			}
		}
		
		try {
			this->graphics.set_color(&black);
			this->graphics.clear();
			this->screen.draw(this);
			this->graphics.draw();
		}
		catch (const std::exception& ex) {
			std::cout << "error drawing graphics:\n"
				<< ex.what();
			return;
		}
		
		try {
			this->audio.clear(this->time.delta);
			
			this->audio.mix_channel(&this->music_channel);
			this->audio.mix_channel(&this->sound_channel);
			
			this->audio.play();
			
		} catch (const std::exception& ex) {
			std::cout << "error playing audio:\n"
				<< ex.what();
			return;
		}
		
		this->time.tick();
	}
}

void demo::Core::quit () {
	this->graphics.close();
	this->audio.close();
	ng::quit();
}


