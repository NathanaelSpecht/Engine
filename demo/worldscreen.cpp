
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

fd::WorldScreen::WorldScreen () {}

fd::WorldScreen::~WorldScreen () {}

void fd::WorldScreen::reset (GameState* gs) {
	// tiles
	this->header.set2(5.0, 1.0, 30.0, 3.0);
	this->canvas.set(&gs->canvas, 1.0, 5.0, 38.0, 24.0);
	// tiles in frame
	this->level1.set("Level 1", 0.33, 1.0, 1.0, 4.0, 3.0);
}

void fd::WorldScreen::event (GameState* gs) {
	// if mouse press level1, then goto levelscreen
	if (gs->event.mode == ng::MousePress) {
		ng::Vec p;
		p.set2(gs->event.mouse.x, gs->event.mouse.y);
		this->canvas.get_mouse(&p);
		
		if (this->level1.contains(&p)) {
			gs->goto_screen(fd::ScreenLevel);
			gs->event.consume();
		}
	}
}

void fd::WorldScreen::draw (GameState* gs) {
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	gs->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_button(&gs->font, &this->level1);
	gs->canvas.draw_rect(&this->header, ng::DrawFrame);
}


