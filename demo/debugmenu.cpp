
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

fd::DebugMenu::DebugMenu () {
	this->events = false;
	this->draws = false;
}

fd::DebugMenu::~DebugMenu () {}

void fd::DebugMenu::reset (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->canvas.set(&gs->canvas, 0.0, 29.0, 40.0, 1.0);
	// tiles in frame
	this->version.set2(0.0, 0.0, 25.0, 1.0);
	this->fps.set2(30.0, 0.0, 10.0, 1.0);
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
	
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	gs->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_rect(&this->version, ng::DrawFrame);
	this->canvas.draw_rect(&this->fps, ng::DrawFrame);
}


