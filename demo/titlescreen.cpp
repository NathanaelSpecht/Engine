
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::TitleScreen::init (GameState* gs) {
	// tiles
	this->header.init(5, 5, 30, 10);
	this->frame.init(14, 20, 12, 5);
	// tiles in frame
	this->start_btn.init(1, 1, 10, 1);
	this->quit_btn.init(1, 3, 10, 1);
}

void fd::TitleScreen::event (GameState* gs) {
	// if mouse press start, then filescreen
	// if mouse press quit, then quit
	if (gs->event->mode == ng::MousePress) {
		ng::Rect p;
		fd::frame_mouse(&p, gs, &this->frame);
		
		if (this->start_btn.contains(p.x, p.y)) {
			gs->screen_mode = fd::FileScreen;
			gs->event.consume();
		} else if (this->quit_btn.contains(p.x, p.y)) {
			gs->screen_mode = fd::None;
			gs->event.consume();
		}
	}
}

void fd::TitleScreen::draw (GameState* gs) {
	fd::frame_draw_rect(&this->header, gs, NULL);
	fd::frame_draw_rect(&this->frame, gs, NULL);
	fd::frame_draw_rect(&this->start_btn, gs, &this->frame);
	fd::frame_draw_rect(&this->quit_btn, gs, &this->frame);
}


