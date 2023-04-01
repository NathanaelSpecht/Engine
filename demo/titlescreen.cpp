
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::TitleScreen::init (GameState* gs) {
	// tiles
	this->header.init2(5.0, 5.0, 30.0, 10.0);
	this->canvas.init(&gs->canvas, 14.0, 20.0, 12.0, 5.0);
	// tiles in frame
	this->start_btn.init2(1.0, 1.0, 10.0, 1.0);
	this->quit_btn.init2(1.0, 3.0, 10.0, 1.0);
}

void fd::TitleScreen::event (GameState* gs) {
	// if mouse press start, then filescreen
	// if mouse press quit, then quit
	if (gs->event.mode == ng::MousePress) {
		ng::Vec p;
		p.init2(static_cast<double>(gs->event.mouse.x), static_cast<double>(gs->event.mouse.y));
		this->canvas.get_mouse(&p);
		
		if (this->start_btn.contains2(p.x, p.y)) {
			gs->goto_screen(fd::ScreenFile);
			gs->event.consume();
		} else if (this->quit_btn.contains2(p.x, p.y)) {
			gs->goto_screen(fd::None);
			gs->event.consume();
		}
	}
}

void fd::TitleScreen::draw (GameState* gs) {
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	this->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
	this->canvas.draw_rect(&this->start_btn, ng::DrawFrame);
	this->canvas.draw_rect(&this->quit_btn, ng::DrawFrame);
	gs->canvas.draw_rect(&this->header, ng::DrawFrame);
}


