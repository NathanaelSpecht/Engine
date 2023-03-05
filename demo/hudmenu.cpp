
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::HudMenu::init (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->frame.init(1, 1, 18, 5);
	// tiles in frame
	this->temp.init(1, 1, 3, 3);
	this->heat.init(5, 1, 13, 2);
	this->fuel.init(5, 3, 13, 1);
}

void fd::HudMenu::event (GameState* gs) {
	// if key press f1, then toggle hudmenu
	if (!this->events) {
		return;
	}
	
	if (gs->event.mode == ng::KeyPress) {
		int k = gs->event.key.scancode;
		
		if (k == SDL_SCANCODE_F1) {
			this->draws = !this->draws;
			gs->event.consume();
		}
	}
}

void fd::HudMenu::draw (GameState* gs) {
	if (!this->draws) {
		return;
	}
	
	fd::frame_draw_rect(&this->frame, gs, NULL);
	fd::frame_draw_rect(&this->temp, gs, &this->frame);
	fd::frame_draw_rect(&this->heat, gs, &this->frame);
	fd::frame_draw_rect(&this->fuel, gs, &this->frame);
}


