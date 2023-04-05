
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

fd::HudMenu::HudMenu () {
	this->events = false;
	this->draws = false;
}

fd::HudMenu::~HudMenu () {}

void fd::HudMenu::reset (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->canvas.set(&gs->canvas, 1.0, 1.0, 18.0, 5.0);
	// tiles in frame
	this->temp.set2(1.0, 1.0, 3.0, 3.0);
	this->heat.set2(5.0, 1.0, 13.0, 2.0);
	this->fuel.set2(5.0, 3.0, 13.0, 1.0);
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
	
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	gs->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_rect(&this->temp, ng::DrawFrame);
	this->canvas.draw_rect(&this->heat, ng::DrawFrame);
	this->canvas.draw_rect(&this->fuel, ng::DrawFrame);
}


