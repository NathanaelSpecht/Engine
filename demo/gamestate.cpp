
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"
#include <iostream>

void fd::frame_mouse(ng::Rect* r, GameState* gs, ng::Rect* frame) {
	r->init(gs->event.mouse.x, gs->event.mouse.y, 0, 0);
	r->portal(&gs->graphics.rect, &gs->rect);
	// frame uses grid coords, so give r grid coords before going relative to frame.
	r->absolute_to_relative(NULL, &gs->tile_grid);
	r->absolute_to_relative(frame, NULL);
}

void fd::frame_draw_rect(const ng::Rect* r, GameState* gs, ng::Rect* frame) {
	ng::Rect r2 = *r;
	// frame uses grid coords, so go absolute before removing grid coords.
	r2.relative_to_absolute(frame, NULL);
	r2.relative_to_absolute(NULL, &gs->tile_grid);
	
	r2.portal(&gs->rect, &gs->graphics.rect);
	gs->graphics.draw_rect(&r2, ng::DrawFrame);
}

void fd::GameState::init () {
	int w, h; // 4:3
	w = 640;
	h = 480;
	
	try {
		ng::init();
		this->graphics.init("Fire Days Demo", w, h);
		this->audio.init();
		this->event.init(&this->graphics);
		this->time.init();
		
	} catch (const std::exception& ex) {
		std::cout << "error at startup:\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->rect.init(0, 0, w, h);
	this->char_grid.init(&this->rect, w/8, h/16); // 8x16 chars
	this->tile_grid.init(&this->rect, w/16, h/16); // 16x16 tiles
	this->background_color.init(0, 0, 0);
	this->draw_color.init(255, 255, 255);
	
	const char* file;
	try {
		this->crazy_music.init(&this->audio, file="game-data/Corncob.wav");
		
	} catch (const std::exception& ex) {
		std::cout << "error loading \"" << file << "\":\n"
			<< ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->music_channel.init();
	this->music_channel.volume = 0.75;
	this->sound_channel.init();
	this->sound_channel.volume = 0.75;
	
	try {
		this->music_channel.play_sound(&this->crazy_music, ng::SoundLoop);
		
		this->screen_mode = fd::None;
		this->title_screen.init(this);
		this->file_screen.init(this);
		this->world_screen.init(this);
		this->level_screen.init(this);
		this->hud_menu.init(this);
		this->pause_menu.init(this);
		this->debug_menu.init(this);
		
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
	this->graphics.quit();
	
	this->music_channel.quit();
	this->sound_channel.quit();
	this->audio.quit();
	
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


