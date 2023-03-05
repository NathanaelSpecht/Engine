
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::DebugMenu::init (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->frame.init(0, 29, 40, 1);
	// tiles in frame
	this->version.init(0, 0, 25, 1);
	this->fps.init(30, 0, 10, 1);
}

void fd::DebugMenu::event (GameState* gs) {
	if (!this->events) {
		return;
	}
	
	// if key press f3, then toggle debugmenu
	if (gs->event.mode == ng::KeyPress) {
		int k = gs->event.key.scancode;
		
		if (k == SDL_SCANCODE_F3) {
			this->draws = !this->draws;
			gs->event.consume();
		}
	}
}

void fd::DebugMenu::draw (GameState* gs) {
	if (!this->draws) {
		return;
	}
	
	fd::frame_draw_rect(&this->frame, gs, NULL);
	fd::frame_draw_rect(&this->version, gs, &this->frame);
	fd::frame_draw_rect(&this->fps, gs, &this->frame);
}


