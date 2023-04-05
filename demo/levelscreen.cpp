
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

fd::LevelScreen::LevelScreen () {}

fd::LevelScreen::~LevelScreen () {}

void fd::LevelScreen::reset (GameState* gs) {
	this->canvas.set(&gs->canvas, 1.0, 1.0, 38.0, 28.0);
}

void fd::LevelScreen::event (GameState* gs) {
	// TODO character controls here.
}

void fd::LevelScreen::draw (GameState* gs) {
	gs->graphics.set_color(&gs->background_color);
	this->canvas.clear();
	gs->graphics.set_color(&gs->draw_color);
	gs->canvas.draw_rect(&this->canvas.space.rect, ng::DrawFrame);
}


