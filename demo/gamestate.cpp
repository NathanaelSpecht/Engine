
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::frame_mouse(ng::Rect* r, GameState* gs, ng::Rect* frame) {
	r.init(gs->event.mouse.x, gs->event.mouse.y, 0, 0);
	r.portal(&gs->graphics.rect, &gs->rect);
	// frame uses grid coords, so give r grid coords before going relative to frame.
	r.absolute_to_relative(NULL, &gs->tile_grid);
	r.absolute_to_relative(frame, NULL);
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
		this->time.init();
		this->graphics.init("Fire Days Demo", w, h);
		//TODO audio & channels
		this->event.init(&this->graphics);
		
	} catch (const std::exception& ex) {
		std::cout << NG_HERE << ": can't init: " << ex.what();
		exit(EXIT_FAILURE);
	}
	
	this->rect.init(0, 0, w, h);
	this->char_grid.init(&this->rect, w/8, h/16); // 8x16 chars
	this->tile_grid.init(&this->rect, w/16, h/16); // 16x16 tiles
	this->background_color.init(0, 0, 0);
	this->draw_color.init(255, 255, 255);
	
	this->screen_mode = fd::ScreenTitle;
	this->title_screen.init(this);
	this->file_screen.init(this);
	this->world_screen.init(this);
	this->level_screen.init(this);
	
	this->hud_mode = fd::None;
	this->hud_menu.init(this);
	
	this->pause_mode = fd::None;
	this->pause_menu.init(this);
	
	this->debug_mode = fd::None;
	this->debug_menu.init(this);
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
		
		{
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
			
			if (this->hud_mode) {
				this->hud_menu.draw(this);
			}
			
			if (this->pause_mode) {
				this->pause_menu.draw(this);
			}
			
			if (this->debug_mode) {
				this->debug_menu.draw(this);
			}
			
			this->graphics.draw();
		}
		
		{ //TODO audio
			/*
			ng_audio_clear(&a);
			ng_audio_mix_channel(&a, &music);
			ng_audio_mix_channel(&a, &sound);
			ng_audio_queue(&a);
			*/
		}
		
		this->time.tick();
		// TODO time.tick(target_millis);
	}
}

void fd::GameState::quit () {
	this->graphics.quit();
	ng::quit();
}


