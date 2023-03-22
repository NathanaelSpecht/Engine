
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::WorldScreen::init (GameState* gs) {
	// tiles
	this->header.init(5, 1, 30, 3);
	this->frame.init(1, 5, 38, 24);
	// tiles in frame
	this->level1.init(1, 1, 4, 3);
}

void fd::WorldScreen::event (GameState* gs) {
	// if mouse press level1, then goto levelscreen
	if (gs->event.mode == ng::MousePress) {
		ng::Rect p;
		fd::frame_mouse(&p, gs, &this->frame);
		
		if (this->level1.contains(p.x, p.y)) {
			gs->goto_screen(fd::ScreenLevel);
			gs->event.consume();
		}
	}
}

void fd::WorldScreen::draw (GameState* gs) {
	fd::frame_draw_rect(&this->header, gs);
	fd::frame_draw_rect(&this->frame, gs);
	fd::frame_draw_rect(&this->level1, gs, &this->frame);
}


