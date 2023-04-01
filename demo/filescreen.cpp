
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::FileScreen::init (GameState* gs) {
	// tiles
	this->header.init2(5.0, 1.0, 30.0, 3.0);
	this->canvas.init(&gs->canvas, 1.0, 5.0, 38.0, 24.0);
	// tiles in frame
	this->save1.init2(1.0, 1.0, 36.0, 5.0);
}

void fd::FileScreen::event (GameState* gs) {
	// if mouse press save1, then goto worldscreen
	if (gs->event.mode == ng::MousePress) {
		ng::Vec p;
		p.init2(gs->event.mouse.x, gs->event.mouse.y);
		this->canvas.get_mouse(&p);
		
		if (this->save1.contains2(p.x, p.y)) {
			gs->goto_screen(fd::ScreenWorld);
			gs->event.consume();
		}
	}
}

void fd::FileScreen::draw (GameState* gs) {
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	this->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_rect(&this->save1, ng::DrawFrame);
	gs->canvas.draw_rect(&this->header, ng::DrawFrame);
}


