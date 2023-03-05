
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::frame_mouse(ngRect* r, GameState* gs, ngRect* frame) {
	ng_rect_init(r, gs->event.mouse.x, gs->event.mouse.y, 0, 0);
	ng_rect_portal(r, &gs->graphics.rect, &gs->rect);
	ng_absolute_to_relative(r, NULL, &gs->tile_grid);
	if (frame != NULL) {
		ng_absolute_to_relative(r, frame, NULL);
	}
}

void fd::frame_draw_rect(const ngRect* r, GameState* gs, ngRect* frame) {
	ngRect r2 = *r;
	if (frame != NULL) {
		ng_relative_to_absolute(&r2, frame, NULL);
	}
	ng_relative_to_absolute(&r2, NULL, &gs->tile_grid);
	ng_rect_portal(&r2, &gs->rect, &gs->graphics.rect);
	ng_draw_rect(&gs->graphics, &r2, NG_FRAME);
}

void fd::GameState::init () {
	int w, h;
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
	
	this->rect.init(0, 0, w, h); // 4:3
	this->char_grid.init(&this->rect, 80, 30); // 80x30 8x16 chars 4:3
	this->tile_grid.init(&this->rect, 40, 30); // 40x30 16x16 tiles 4:3
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
			}
			
			switch (this->debug_mode) {
				case fd::MenuDebug: {
					this->debug_menu.event(this);
				} default: {}
			}
			
			switch (this->pause_mode) {
				case fd::MenuPause: {
					this->pause_menu.event(this);
				} default: {}
			}
			
			switch (this->hud_mode) {
				case fd::MenuHud: {
					this->hud_menu.event(this);
				} default: {}
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
			
			switch (this->hud_mode) {
				case fd::MenuHud: {
					this->hud_menu.draw(this);
				} default: {}
			}
			
			switch (this->pause_mode) {
				case fd::MenuPause: {
					this->pause_menu.draw(this);
				} default: {}
			}
			
			switch (this->debug_mode) {
				case fd::MenuDebug: {
					this->debug_menu.draw(this);
				} default: {}
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
	}
}

void fd::GameState::quit () {
	this->graphics.quit();
	ng::quit();
}


