
/* Copyright (C) 2022 - 2023 Nathanael Specht */

#include "firedays.h"

void fd::LevelScreen::init (GameState* gs) {
	this->frame.init(1, 1, 38, 28);
}

void fd::LevelScreen::event (GameState* gs) {
	// TODO character controls here.
}

void fd::LevelScreen::draw (GameState* gs) {
	fd::frame_draw_rect(&this->frame, gs);
}


