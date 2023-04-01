
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::PauseMenu::init (GameState* gs) {
	this->events = false;
	this->draws = false;
	// tiles
	this->header.init2(5.0, 5.0, 30.0, 3.0);
	this->canvas.init(&gs->canvas, 14.0, 13.0, 12.0, 5.0);
	// tiles in frame
	this->resume_btn.init2(1.0, 1.0, 10.0, 1.0);
	this->quit_btn.init2(1.0, 3.0, 10.0, 1.0);
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
		ng::Vec p;
		p.init2(gs->event.mouse.x, gs->event.mouse.y);
		this->canvas.get_mouse(&p);
		
		if (this->resume_btn.contains2(p.x, p.y)) {
			this->draws = false;
			gs->event.consume();
		} else if (this->quit_btn.contains2(p.x, p.y)) {
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
	
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	gs->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_rect(&this->resume_btn, ng::DrawFrame);
	this->canvas.draw_rect(&this->quit_btn, ng::DrawFrame);
	gs->canvas.draw_rect(&this->header, ng::DrawFrame);
}


