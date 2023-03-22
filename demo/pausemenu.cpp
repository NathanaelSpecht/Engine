
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::PauseMenu::init (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->header.init(5, 5, 30, 3);
	this->frame.init(14, 13, 12, 5);
	// tiles in frame
	this->resume_btn.init(1, 1, 10, 1);
	this->quit_btn.init(1, 3, 10, 1);
}

void fd::PauseMenu::event (GameState* gs) {
	if (!this->events) {
		return;
	}
	
	// if key press escape, then toggle pausemenu
	if (gs->event.mode == ng::KeyPress) {
		int k = gs->event.key.scancode;
		
		if (k == SDL_SCANCODE_ESCAPE) {
			this->draws = !this->draws;
			gs->event.consume();
			return;
		}
	}
	
	// if mouse press resume, then hide pausemenu
	// if mouse press quit, then:
	// - if levelscreen, then goto worldscreen
	// - if worldscreen or filescreen, then goto titlescreen
	// - if titlescreen, then quit
	if (this->draws && gs->event.mode == ng::MousePress) {
		ng::Rect p;
		fd::frame_mouse(&p, gs, &this->frame);
		
		if (this->resume_btn.contains(p.x, p.y)) {
			this->draws = false;
			gs->event.consume();
		} else if (this->quit_btn.contains(p.x, p.y)) {
			switch (gs->screen_mode) {
				case fd::ScreenLevel: {
					gs->goto_screen(fd::ScreenWorld);
					break;
				} case fd::ScreenWorld: case fd::ScreenFile: {
					gs->goto_screen(fd::ScreenTitle);
					break;
				} case fd::ScreenTitle: {
					gs->goto_screen(fd::None);
					break;
				} default: {}
			}
			gs->event.consume();
		}
	}
}

void fd::PauseMenu::draw (GameState* gs) {
	if (!this->draws) {
		return;
	}
	
	fd::frame_draw_rect(&this->header, gs);
	fd::frame_draw_rect(&this->frame, gs);
	fd::frame_draw_rect(&this->resume_btn, gs, &this->frame);
	fd::frame_draw_rect(&this->quit_btn, gs, &this->frame);
}


