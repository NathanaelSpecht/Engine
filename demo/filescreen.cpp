
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::FileScreen::init (GameState* gs) {
	// tiles
	this->header.init(5, 1, 30, 3);
	this->frame.init(1, 5, 38, 24);
	// tiles in frame
	this->save1.init(1, 1, 36, 5);
}

void fd::FileScreen::event (GameState* gs) {
	// if mouse press save1, then goto worldscreen
	if (gs->event.mode == ng::MousePress) {
		ng::Rect p;
		fd::frame_mouse(&p, gs, &this->frame);
		
		if (this->save1.contains(p.x, p.y)) {
			gs->goto_screen(fd::ScreenWorld);
			gs->event.consume();
		}
	}
}

void fd::FileScreen::draw (GameState* gs) {
	fd::frame_draw_rect(&this->header, gs);
	fd::frame_draw_rect(&this->frame, gs);
	fd::frame_draw_rect(&this->save1, gs, &this->frame);
}


