
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"
#include <iostream>

fd::GameState::GameState () {
	this->screen_mode = fd::None;
}

fd::GameState::~GameState () {}

void fd::GameState::reset () {
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
	
	const char* file;
	ng::Color color_key;
	color_key.set(0, 0, 0);
	try {
		this->text.load(&this->graphics, file="game-data/text.bmp", &color_key);
		this->crazy_music.load(&this->audio, file="game-data/Corncob.wav");
		
	} catch (const std::exception& ex) {
		std::cout << "error loading \"" << file << "\":\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->font.set_c(&this->text, &this->text.rect, 32.0, 6.0);
	this->font.offset.set2(0.0, -1.0);
	this->canvas.set_i(&this->graphics, 16.0, 16.0);
	this->canvas.space.const_c = true;
	this->background_color.set(0, 0, 0);
	this->draw_color.set(255, 255, 255);
	
	//this->music_channel.set();
	this->music_channel.volume = 0.75;
	//this->sound_channel.init();
	this->sound_channel.volume = 0.75;
	
	try {
		this->music_channel.play_sound(&this->crazy_music, ng::SoundLoop);
		
		this->screen_mode = fd::None;
		this->title_screen.reset(this);
		this->file_screen.reset(this);
		this->world_screen.reset(this);
		this->level_screen.reset(this);
		this->hud_menu.reset(this);
		this->pause_menu.reset(this);
		this->debug_menu.reset(this);
		
	} catch (const std::exception& ex) {
		std::cout << "error configuring data:\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->goto_screen(fd::ScreenTitle);
}

void fd::GameState::loop () {
	while (true) {
		while (this->event.next()) {
			if (this->event.mode == ng::Quit) {
				return;
			} else if (this->event.mode == ng::WindowEvent) {
				// optionally resize screens and menus to fit window.
				continue;
			}
			
			// Find place to process event, then consume event.
			
			this->debug_menu.event(this);
			if (!this->event.exists()) {
				continue;
			}
			
			this->hud_menu.event(this);
			if (!this->event.exists()) {
				continue;
			}
			
			this->pause_menu.event(this);
			if (!this->event.exists()) {
				continue;
			}
			
			switch (this->screen_mode) {
				case fd::ScreenTitle: {
					this->title_screen.event(this);
					break;
				} case fd::ScreenFile: {
					this->file_screen.event(this);
					break;
				} case fd::ScreenWorld: {
					this->world_screen.event(this);
					break;
				} case fd::ScreenLevel: {
					this->level_screen.event(this);
					break;
				} default: {
					return;
				}
			}
		}
		
		try {
			this->graphics.set_color(&this->background_color);
			this->graphics.clear();
			
			this->graphics.set_color(&this->draw_color);
			switch (this->screen_mode) {
				case fd::ScreenTitle: {
					this->title_screen.draw(this);
					break;
				} case fd::ScreenFile: {
					this->file_screen.draw(this);
					break;
				} case fd::ScreenWorld: {
					this->world_screen.draw(this);
					break;
				} case fd::ScreenLevel: {
					this->level_screen.draw(this);
					break;
				} default: {
					return;
				}
			}
			
			this->hud_menu.draw(this);
			this->pause_menu.draw(this);
			this->debug_menu.draw(this);
			
			this->graphics.draw();
			
		} catch (const std::exception& ex) {
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

void fd::GameState::quit () {
	this->graphics.close();
	
	//this->music_channel.quit();
	//this->sound_channel.quit();
	this->audio.close();
	
	ng::quit();
}

void fd::GameState::goto_screen (int screen_mode) {
	this->screen_mode = screen_mode;
	
	this->debug_menu.events = true;
	//this->debug_menu.draws = false;
	
	this->pause_menu.events = true;
	this->pause_menu.draws = false;
	
	if (screen_mode == fd::ScreenLevel) {
		this->hud_menu.events = true;
		this->hud_menu.draws = true;
	} else {
		this->hud_menu.events = false;
		this->hud_menu.draws = false;
	}
}


